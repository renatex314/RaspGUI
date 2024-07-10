#ifndef _DRAWER_HPP
#define _DRAWER_HPP

namespace uikit
{
    class Drawer
    {
    public:
        virtual void dispatch_redraw_request() = 0;
    };
}

#endif