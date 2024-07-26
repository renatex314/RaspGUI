#include <SDL2/SDL.h>
#include <iostream>
#include "../utils/utils.hpp"
#include "drawer/drawer.hpp"
#include "assets_handler/assets_handler.hpp"

#ifndef _CONTEXT_H
#define _CONTEXT_H

namespace uikit
{
    class Context
    {
    public:
        Context(SDL_Renderer *renderer);
        Context(Context *context);

        Drawer *get_drawer();
        void set_drawer(Drawer *drawer);
        AssetsHandler *get_assets_handler();
        void set_assets_handler(AssetsHandler *assets_handler);
        std::string get_application_path();
        void set_application_path(std::string application_path);

    protected:
        SDL_Renderer *get_renderer();

    private:
        Context();

        Drawer *drawer;
        AssetsHandler *assets_handler;
        SDL_Renderer *renderer;
        std::string application_path;
    };
}

#endif