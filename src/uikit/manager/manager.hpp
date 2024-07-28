#include "../context/context.hpp"
#include "../context/drawer/drawer.hpp"
#include "../context/assets_handler/assets_handler.hpp"
#include "../widget/widget.hpp"
#include "../event/event.hpp"

#ifndef _MANAGER_H
#define _MANAGER_H

namespace uikit
{
    class Manager : public Context, public Drawer, public AssetsHandler
    {
    public:
        Manager(Context *context);

        void render();
        void dispatch_redraw_request();
        void handle_event(SDL_Event event);
        std::string get_resource_path(std::string resource_name);
        event::mouse::MouseEvent get_mouse_event(SDL_Event event);
        event::keyboard::KeyEvent get_keyboard_event(SDL_Event event);

        void attach_root(Widget *root);
        Widget *get_root();

    private:
        Manager();

        bool needs_redraw;
        SDL_Texture *window_texture;
        Widget *root;
    };
}

#endif