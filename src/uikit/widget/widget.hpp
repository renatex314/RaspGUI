#include "../context/context.hpp"
#include <SDL2/SDL.h>
#include <vector>

#ifndef _WIDGET_H
#define _WIDGET_H

class Widget : public Context
{
public:
    Widget(Context *context);
    void draw();

protected:
    virtual void perform_draw(SDL_Renderer *renderer);

private:
    int x, y;
    int width, height;
    int z_index;
    SDL_Texture *texture;
};

#endif