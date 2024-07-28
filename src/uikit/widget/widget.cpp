#include "widget.hpp"

using namespace uikit;

Widget::Widget() : Context((SDL_Renderer *)NULL)
{
    throw std::runtime_error("Widget should be instantiated with a Context object.");
};

Widget::Widget(Context *context) : Context(context)
{
    this->needs_redraw = true;
    this->allows_resizing = false;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->margin_left = 0;
    this->margin_top = 0;
    this->margin_right = 0;
    this->margin_bottom = 0;
    this->z_index = 0;
    this->texture = SDL_CreateTexture(this->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 0, 0);
};

Widget::~Widget()
{
    if (this->texture != NULL)
        SDL_DestroyTexture(this->texture);
}

bool Widget::get_needs_redraw()
{
    return this->needs_redraw;
}

bool Widget::get_allows_resizing()
{
    return this->allows_resizing;
}

int Widget::get_x()
{
    return this->x;
}

int Widget::get_y()
{
    return this->y;
}

int Widget::get_width()
{
    return this->width;
}

int Widget::get_height()
{
    return this->height;
}

int Widget::get_margin_left()
{
    return this->margin_left;
}

int Widget::get_margin_top()
{
    return this->margin_top;
}

int Widget::get_margin_right()
{
    return this->margin_right;
}

int Widget::get_margin_bottom()
{
    return this->margin_bottom;
}

int Widget::get_z_index()
{
    return this->z_index;
}

void Widget::set_allows_resizing(bool allows_resizing)
{
    this->allows_resizing = allows_resizing;
}

void Widget::set_x(int x)
{
    this->set_position(x, this->y);
}

void Widget::set_y(int y)
{
    this->set_position(this->x, y);
}

void Widget::set_position(int x, int y)
{
    this->set_x(x);
    this->set_y(y);
}

void Widget::set_width(int width)
{
    this->set_size(width, this->height);
}

void Widget::set_height(int height)
{
    this->set_size(this->width, height);
}

void Widget::set_size(int width, int height)
{
    int last_width = this->width;
    int last_height = this->height;

    this->width = width;
    this->height = height;

    if (this->width != last_width || this->height != last_height)
    {
        this->resize_texture();
        this->dispatch_redraw_request();
        this->on_resize();
    }
}

void Widget::set_margin_left(int margin_left)
{
    this->margin_left = margin_left;
}

void Widget::set_margin_top(int margin_top)
{
    this->margin_top = margin_top;
}

void Widget::set_margin_right(int margin_right)
{
    this->margin_right = margin_right;
}

void Widget::set_margin_bottom(int margin_bottom)
{
    this->margin_bottom = margin_bottom;
}

void Widget::set_margin(int margin)
{
    this->set_margin_left(margin);
    this->set_margin_top(margin);
    this->set_margin_right(margin);
    this->set_margin_bottom(margin);
}

void Widget::set_z_index(int z_index)
{
    this->z_index = z_index;
}

void Widget::resize_texture()
{
    SDL_Texture *default_texture = SDL_GetRenderTarget(this->get_renderer());

    SDL_Texture *resized_texture = SDL_CreateTexture(this->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
    SDL_SetRenderTarget(this->get_renderer(), resized_texture);
    SDL_RenderCopy(this->get_renderer(), this->texture, NULL, NULL);
    SDL_SetRenderTarget(this->get_renderer(), default_texture);
    SDL_DestroyTexture(this->texture);

    this->texture = resized_texture;
}

void Widget::dispatch_redraw_request()
{
    this->needs_redraw = true;

    Drawer *drawer = this->get_drawer();
    if (drawer != NULL)
        drawer->dispatch_redraw_request();
}

// To Be Implemented by Subclasses
void Widget::perform_draw(SDL_Renderer *renderer) {};

SDL_Texture *Widget::draw()
{
    if (this->needs_redraw)
    {
        SDL_Renderer *renderer = this->get_renderer();
        SDL_Texture *default_texture = SDL_GetRenderTarget(renderer);
        SDL_SetRenderTarget(renderer, this->texture);
        this->perform_draw(renderer);
        SDL_SetRenderTarget(renderer, default_texture);

        this->needs_redraw = false;
    }

    return this->texture;
}

// Methods that can be overridden by subclasses
void Widget::on_mouse_down(event::mouse::MouseEvent event) {};
void Widget::on_mouse_up(event::mouse::MouseEvent event) {};
void Widget::on_mouse_move(event::mouse::MouseEvent event) {};
void Widget::on_mouse_wheel(event::mouse::MouseEvent event) {};
void Widget::on_key_down(event::keyboard::KeyEvent event) {};
void Widget::on_key_up(event::keyboard::KeyEvent event) {};
void Widget::on_resize() {};