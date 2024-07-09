#include "manager.hpp"

Manager::Manager() : Context((SDL_Renderer *)NULL)
{
    throw std::runtime_error("Manager should be instantiated with a Context object.");
};

Manager::Manager(Context *context) : Context(context)
{
    this->set_drawer(this);
};

void Manager::attach_root(Widget *root)
{
    this->root = root;
}

Widget *Manager::get_root()
{
    return this->root;
}

// TODO: To be implemented
void Manager::handle_redraw_request()
{
    Widget *root = this->get_root();
    if (root != NULL)
    {
        root->draw();
    }
}