#include <SDL2/SDL.h>
#include <iostream>
#include "drawer/drawer.hpp"

#ifndef _CONTEXT_H
#define _CONTEXT_H

class Context
{
public:
    Context(SDL_Renderer *renderer);
    Context(Context *context);

    Drawer *get_drawer();
    void set_drawer(Drawer *drawer);

protected:
    SDL_Renderer *get_renderer();

private:
    Context();
    void init();

    Drawer *drawer;
    SDL_Renderer *renderer;
};

#endif