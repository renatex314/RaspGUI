#include "widget.hpp"

Widget::Widget() : Context((SDL_Renderer *)NULL)
{
    throw std::runtime_error("Widget should be instantiated with a Context object.");
};

Widget::Widget(Context *context) : Context(context)
{
    this->needs_redraw = true;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->z_index = 0;
    this->texture = SDL_CreateTexture(this->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 0, 0);
};

bool Widget::get_needs_redraw()
{
    return this->needs_redraw;
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

int Widget::get_z_index()
{
    return this->z_index;
}

void Widget::set_x(int x)
{
    this->x = x;
}

void Widget::set_y(int y)
{
    this->y = y;
}

void Widget::set_width(int width)
{
    this->width = width;
}

void Widget::set_height(int height)
{
    this->height = height;
}

void Widget::set_z_index(int z_index)
{
    this->z_index = z_index;
}

void Widget::dispatch_redraw_request()
{
    this->needs_redraw = true;

    Drawer *drawer = this->get_drawer();
    if (drawer != NULL)
        drawer->handle_redraw_request();
}

// To Be Implemented by Subclasses
void Widget::perform_draw(SDL_Renderer *renderer) {};

SDL_Texture *Widget::draw()
{
    SDL_Renderer *renderer = this->get_renderer();
    SDL_Texture *default_texture = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, this->texture);

    if (this->needs_redraw)
        this->perform_draw(renderer);

    SDL_SetRenderTarget(renderer, default_texture);

    return this->texture;
}
