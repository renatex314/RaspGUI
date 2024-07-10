#include "context.hpp"

using namespace uikit;

Context::Context()
{
    throw std::runtime_error("Context should be instantiated with a renderer or another Context.");
}

Context::Context(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->drawer = NULL;
}

Context::Context(Context *context)
{
    this->renderer = context->get_renderer();
    this->drawer = context->get_drawer();
}

Drawer *Context::get_drawer()
{
    return this->drawer;
}

void Context::set_drawer(Drawer *drawer)
{
    this->drawer = drawer;
}

SDL_Renderer *Context::get_renderer()
{
    return this->renderer;
}