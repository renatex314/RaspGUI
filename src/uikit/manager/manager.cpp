#include "manager.hpp"

using namespace uikit;

Manager::Manager() : Context((SDL_Renderer *)NULL)
{
    throw std::runtime_error("Manager should be instantiated with a Context object.");
};

Manager::Manager(Context *context) : Context(context)
{
    this->set_drawer(this);
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
            output_rect.x = root->get_x();
            output_rect.y = root->get_y();
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

void Manager::handle_event(SDL_Event sdl_event)
{
    if (sdl_event.type == SDL_MOUSEBUTTONUP || sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEMOTION || sdl_event.type == SDL_MOUSEWHEEL)
    {
        event::mouse::MouseEvent event = this->get_mouse_event(sdl_event);
        Widget *root = this->get_root();
        if (root != NULL)
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
}