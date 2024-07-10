#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../context/context.hpp"
#include "../event/event.hpp"

#ifndef _WIDGET_H
#define _WIDGET_H

namespace uikit
{
    class Widget : public Context
    {
    public:
        Widget(Context *context);
        ~Widget();
        SDL_Texture *draw();

        bool get_needs_redraw();
        int get_x();
        int get_y();
        int get_width();
        int get_height();
        int get_z_index();

        void dispatch_redraw_request();
        void set_x(int x);
        void set_y(int y);
        void set_width(int width);
        void set_height(int height);
        void set_z_index(int z_index);

        virtual void on_mouse_down(event::mouse::MouseEvent event);
        virtual void on_mouse_up(event::mouse::MouseEvent event);
        virtual void on_mouse_move(event::mouse::MouseEvent event);
        virtual void on_mouse_wheel(event::mouse::MouseEvent event);

    protected:
        virtual void perform_draw(SDL_Renderer *renderer);

    private:
        Widget();

        void resize_texture();

        bool needs_redraw;
        int x, y;
        int width, height;
        int z_index;
        SDL_Texture *texture;
    };
}

#endif