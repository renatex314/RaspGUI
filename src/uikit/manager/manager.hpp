#include "../context/context.hpp"
#include "../context/drawer/drawer.hpp"
#include "../widget/widget.hpp"

#ifndef _MANAGER_H
#define _MANAGER_H

namespace uikit
{
    class Manager : public Context, public Drawer
    {
    public:
        Manager(Context *context);

        void render();
        void dispatch_redraw_request();

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