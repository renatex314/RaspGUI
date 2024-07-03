#include "context.hpp"

Context::Context(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

Context::Context(Context *context)
{
    this->renderer = context->get_renderer();
}