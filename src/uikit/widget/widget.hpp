#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "../context/context.hpp"
#include "../event/event.hpp"

#ifndef _WIDGET_H
#define _WIDGET_H

#define LISTENER_TIMEOUT_WARNING 50

typedef void (*EventListenerCallback)(void *event, void *params);

namespace uikit
{
    /*
        The type of event that the widget is dispatching.
        Not all types of events can be dispatched. Ex: "RESIZE"
    */
    enum WidgetEventType
    {
        MOUSE,
        KEYBOARD,
        RESIZE
    };

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
        Widget *get_parent();

        void dispatch_redraw_request();
        void dispatch_event(WidgetEventType event_type, void *event);
        /*
            Attach a listener to an event type and action.
            @return The listener function.
        */
        EventListenerCallback attach_listener(WidgetEventType event_type, EventAction action, EventListenerCallback listener, void *params);
        /*
            Attach a listener to an event type and action. It considers that the event has no action.
            @return The listener function.
        */
        EventListenerCallback attach_listener(WidgetEventType event_type, EventListenerCallback listener, void *params);
        void remove_listener(WidgetEventType event_type, EventAction action, EventListenerCallback listener);
        void clear_listeners(WidgetEventType event_type, EventAction action);
        void clear_all_listeners();
        void set_layout_allows_resizing(bool allows_resizing);
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
        void set_parent(Widget *parent);

    private:
        Widget();

        void resize_texture();
        void execute_listeners(WidgetEventType event_type, EventAction action, void *event);

        bool needs_redraw, allows_resizing;
        int x, y;
        int width, height;
        int margin_left, margin_top, margin_right, margin_bottom;
        int z_index;
        SDL_Texture *texture;
        Widget *parent;

        std::map<
            WidgetEventType,
            std::map<
                EventAction,
                std::set<
                    std::tuple<EventListenerCallback, void *>>>>
            event_listeners;
    };
}

#endif