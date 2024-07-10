#include "simple_widget.hpp"

SimpleWidget::SimpleWidget(Context *context) : Widget(context)
{
    this->set_width(800);
    this->set_height(600);
    this->bg_intensity = 100;
}

void SimpleWidget::perform_draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, this->bg_intensity, this->bg_intensity, this->bg_intensity, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 800, 600);
    SDL_RenderDrawLine(renderer, 800, 0, 0, 600);
}