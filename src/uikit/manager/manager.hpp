#include "../context/context.hpp"
#include "../context/drawer/drawer.hpp"
#include "../widget/widget.hpp"

#ifndef _MANAGER_H
#define _MANAGER_H

class Manager : public Context, public Drawer
{
public:
    Manager(Context *context);
    void handle_redraw_request();
    void attach_root(Widget *root);
    Widget *get_root();

private:
    Manager();

    Widget *root;
};

#endif