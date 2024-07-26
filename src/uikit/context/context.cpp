#include "context.hpp"

using namespace uikit;

Context::Context()
{
    throw std::runtime_error("Context should be instantiated with a renderer or another Context.");
}

Context::Context(SDL_Renderer *renderer)
{
    this->drawer = NULL;
    this->assets_handler = NULL;
    this->renderer = renderer;
    this->application_path = Utils::get_application_path();
}

Context::Context(Context *context)
{
    this->drawer = context->get_drawer();
    this->assets_handler = context->get_assets_handler();
    this->renderer = context->get_renderer();
    this->application_path = context->get_application_path();
}

Drawer *Context::get_drawer()
{
    return this->drawer;
}

void Context::set_drawer(Drawer *drawer)
{
    this->drawer = drawer;
}

AssetsHandler *Context::get_assets_handler()
{
    return this->assets_handler;
}

void Context::set_assets_handler(AssetsHandler *assets_handler)
{
    this->assets_handler = assets_handler;
}

SDL_Renderer *Context::get_renderer()
{
    return this->renderer;
}

void Context::set_application_path(std::string application_path)
{
    this->application_path = application_path;
}

std::string Context::get_application_path()
{
    return this->application_path;
}