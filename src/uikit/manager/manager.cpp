#include "manager.hpp"

using namespace uikit;

Manager::Manager() : Context((SDL_Renderer *)NULL)
{
    throw std::runtime_error("Manager should be instantiated with a Context object.");
};

Manager::Manager(Context *context) : Context(context)
{
    this->set_drawer(this);
    this->set_assets_handler(this);
    this->window_texture = SDL_GetRenderTarget(this->get_renderer());
    this->needs_redraw = true;
};

void Manager::attach_root(Widget *root)
{
    this->root = root;
}

Widget *Manager::get_root()
{
    return this->root;
}

void Manager::render()
{
    if (this->needs_redraw)
    {
        SDL_Renderer *renderer = this->get_renderer();

        SDL_SetRenderTarget(renderer, this->window_texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Widget *root = this->get_root();
        if (root != NULL)
        {
            SDL_Texture *output = root->draw();
            SDL_Rect output_rect;
            output_rect.x = root->get_x() + (root->get_margin_left() - root->get_margin_right());
            output_rect.y = root->get_y() + (root->get_margin_top() - root->get_margin_bottom());
            output_rect.w = root->get_width();
            output_rect.h = root->get_height();

            SDL_SetRenderTarget(this->get_renderer(), this->window_texture);
            SDL_RenderCopy(this->get_renderer(), output, NULL, &output_rect);
        }

        SDL_RenderPresent(renderer);

        this->needs_redraw = false;
    }
}

void Manager::dispatch_redraw_request()
{
    this->needs_redraw = true;
}

event::mouse::MouseEvent Manager::get_mouse_event(SDL_Event event)
{
    event::mouse::MouseEvent mouse_event;
    mouse_event.x = event.button.x;
    mouse_event.y = event.button.y;
    mouse_event.wheel_x = event.wheel.x;
    mouse_event.wheel_y = event.wheel.y;

    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        mouse_event.button = event::mouse::MOUSE_BUTTON_LEFT;
        break;
    case SDL_BUTTON_MIDDLE:
        mouse_event.button = event::mouse::MOUSE_BUTTON_MIDDLE;
        break;
    case SDL_BUTTON_RIGHT:
        mouse_event.button = event::mouse::MOUSE_BUTTON_RIGHT;
        break;

    default:
        mouse_event.button = event::mouse::MOUSE_BUTTON_LEFT;
        break;
    }

    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        mouse_event.type = event::mouse::MOUSE_DOWN;
        break;
    case SDL_MOUSEBUTTONUP:
        mouse_event.type = event::mouse::MOUSE_UP;
        break;
    case SDL_MOUSEMOTION:
        mouse_event.type = event::mouse::MOUSE_MOVE;
        break;
    }

    return mouse_event;
}

event::keyboard::KeyEvent Manager::get_keyboard_event(SDL_Event event)
{
    event::keyboard::KeyEvent keyboard_event;
    keyboard_event.sdl_key_code = event.key.keysym.sym;

    switch (event.type)
    {
    case SDL_KEYDOWN:
        keyboard_event.type = event::keyboard::KEY_DOWN;
        break;
    case SDL_KEYUP:
        keyboard_event.type = event::keyboard::KEY_UP;
        break;
    }

    return keyboard_event;
}

void Manager::handle_event(SDL_Event sdl_event)
{
    if (sdl_event.type == SDL_MOUSEBUTTONUP || sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEMOTION || sdl_event.type == SDL_MOUSEWHEEL)
    {
        event::mouse::MouseEvent event = this->get_mouse_event(sdl_event);
        Widget *root = this->get_root();
        if (root != nullptr)
        {
            switch (event.type)
            {
            case event::mouse::MOUSE_DOWN:
                root->on_mouse_down(event);
                break;
            case event::mouse::MOUSE_UP:
                root->on_mouse_up(event);
                break;
            case event::mouse::MOUSE_MOVE:
                root->on_mouse_move(event);
                break;
            case event::mouse::MOUSE_WHEEL:
                root->on_mouse_wheel(event);
                break;
            }
        }
    }

    if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP)
    {
        event::keyboard::KeyEvent event = this->get_keyboard_event(sdl_event);
        Widget *root = this->get_root();
        if (root != nullptr)
        {
            switch (event.type)
            {
            case event::keyboard::KEY_DOWN:
                root->on_key_down(event);
                break;
            case event::keyboard::KEY_UP:
                root->on_key_up(event);
                break;
            }
        }
    }

    if (sdl_event.type == SDL_WINDOWEVENT)
    {
        if (sdl_event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            uikit::Widget *root = this->get_root();

            if (root != nullptr)
            {
                root->set_size(sdl_event.window.data1, sdl_event.window.data2);
            }
        }
    }
}

std::string Manager::get_resource_path(std::string resource_name)
{
    std::string resource_path = this->get_application_path() + "assets/" + resource_name;

    if (Utils::file_exists(resource_path))
    {
        return resource_path;
    }

    throw std::runtime_error("Resource not found: " + resource_path);
}