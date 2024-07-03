#include "widget.hpp"

Widget::Widget(Context *context) : Context(context)
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->z_index = 0;
    this->texture = SDL_CreateTexture(this->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 0, 0);
};

// To Be Implemented by Subclasses
void Widget::perform_draw(SDL_Renderer *renderer) {};

void Widget::draw()
{
    this->perform_draw(this->get_renderer());
}
