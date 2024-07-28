#include "widget_group.hpp"

using namespace uikit;

WidgetGroup::WidgetGroup(Context *context) : Widget(context)
{
}

WidgetGroup::~WidgetGroup()
{
    std::cout << "WidgetGroup::~WidgetGroup()" << std::endl;
}

void WidgetGroup::perform_draw(SDL_Renderer *renderer)
{
}