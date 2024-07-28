#include <iostream>
#include <map>
#include <vector>
#include "../widget/widget.hpp"

#ifndef _WIDGET_GROUP_H
#define _WIDGET_GROUP_H

namespace uikit
{
    class WidgetGroup : public Widget
    {
    public:
        WidgetGroup(Context *context);
        ~WidgetGroup();

    protected:
        virtual void perform_draw(SDL_Renderer *renderer);

    private:
        std::map<int, std::vector<Widget *>> widgets;
    };
};

#endif