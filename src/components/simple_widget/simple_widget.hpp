#include <iostream>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>
#include "../../uikit/widget/widget.hpp"
#include "../../uikit/context/context.hpp"

#ifndef _SIMPLE_WIDGET_H
#define _SIMPLE_WIDGET_H

class SimpleWidget : public uikit::Widget
{
public:
    SimpleWidget(Context *context);
    ~SimpleWidget();
    void on_mouse_down(uikit::event::mouse::MouseEvent event);
    void on_mouse_move(uikit::event::mouse::MouseEvent event);
    void on_mouse_up(uikit::event::mouse::MouseEvent event);
    void on_key_up(uikit::event::keyboard::KeyEvent event);

private:
    void perform_draw(SDL_Renderer *renderer);
    void draw_current_time(SDL_Renderer *renderer);
    static int SDLCALL redraw_timer(void *data);
    SDL_Thread *running_thread;
    TTF_Font *font;

    bool is_mouse_down;
    int mouse_x, mouse_y;
    Uint8 bg_intensity;
};

#endif