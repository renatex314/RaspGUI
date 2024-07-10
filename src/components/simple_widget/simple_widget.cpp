#include "simple_widget.hpp"

using namespace uikit;

SimpleWidget::SimpleWidget(Context *context) : Widget(context)
{
    this->set_width(800);
    this->set_height(600);
    this->bg_intensity = 100;
    this->is_mouse_down = false;
    this->mouse_x = 0;
    this->mouse_y = 0;
}

void SimpleWidget::perform_draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, this->bg_intensity, this->bg_intensity, this->bg_intensity, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, this->mouse_x, this->mouse_y, 800, 600);
    SDL_RenderDrawLine(renderer, this->mouse_x, this->mouse_y, 800, 0);
    SDL_RenderDrawLine(renderer, 0, 0, this->mouse_x, this->mouse_y);
    SDL_RenderDrawLine(renderer, 0, 600, this->mouse_x, this->mouse_y);
}

void SimpleWidget::on_mouse_down(event::mouse::MouseEvent event)
{
    this->is_mouse_down = true;
    this->bg_intensity = 100;
    this->dispatch_redraw_request();
}

void SimpleWidget::on_mouse_move(event::mouse::MouseEvent event)
{
    this->mouse_x = event.x;
    this->mouse_y = event.y;

    if (!this->is_mouse_down)
    {
        this->bg_intensity = (event.x / 800.0) * 200.0;
        this->dispatch_redraw_request();
    }
}

void SimpleWidget::on_mouse_up(event::mouse::MouseEvent event)
{
    this->is_mouse_down = false;
    this->bg_intensity = 200;
    this->dispatch_redraw_request();
}