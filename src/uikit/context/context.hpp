#include <SDL2/SDL.h>

#ifndef _CONTEXT_H
#define _CONTEXT_H

class Context
{
public:
    Context(SDL_Renderer *renderer);
    Context(Context *context);

protected:
    SDL_Renderer *get_renderer();

private:
    Context();
    SDL_Renderer *renderer;
};

#endif