#include "manager.hpp"

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