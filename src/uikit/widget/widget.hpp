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
        virtual ~Widget();
        SDL_Texture *draw();

        bool get_needs_redraw();
        bool get_allows_resizing();
        int get_x();
        int get_y();
        int get_width();
        int get_height();
        int get_margin_left();
        int get_margin_top();
        int get_margin_right();
        int get_margin_bottom();
        int get_z_index();

        void dispatch_redraw_request();
        void set_allows_resizing(bool allows_resizing);
        void set_x(int x);
        void set_y(int y);
        void set_position(int x, int y);
        void set_width(int width);
        void set_height(int height);
        void set_size(int width, int height);
        void set_margin_left(int margin_left);
        void set_margin_top(int margin_top);
        void set_margin_right(int margin_right);
        void set_margin_bottom(int margin_bottom);
        void set_margin(int margin);
        void set_z_index(int z_index);

        virtual void on_mouse_down(event::mouse::MouseEvent event);
        virtual void on_mouse_up(event::mouse::MouseEvent event);
        virtual void on_mouse_move(event::mouse::MouseEvent event);
        virtual void on_mouse_wheel(event::mouse::MouseEvent event);
        virtual void on_key_down(event::keyboard::KeyEvent event);
        virtual void on_key_up(event::keyboard::KeyEvent event);
        virtual void on_resize();

    protected:
        virtual void perform_draw(SDL_Renderer *renderer);

    private:
        Widget();

        void resize_texture();

        bool needs_redraw, allows_resizing;
        int x, y;
        int width, height;
        int margin_left, margin_top, margin_right, margin_bottom;
        int z_index;
        SDL_Texture *texture;
    };
}

#endif