#include <iostream>
#include <SDL2/SDL_thread.h>
#include "../../uikit/widget/widget.hpp"
#include "../../uikit/context/context.hpp"

#ifndef _SIMPLE_WIDGET_H
#define _SIMPLE_WIDGET_H

class SimpleWidget : public Widget
{
public:
    SimpleWidget(Context *context);

private:
    void perform_draw(SDL_Renderer *renderer);

    Uint8 bg_intensity;
};

#endif