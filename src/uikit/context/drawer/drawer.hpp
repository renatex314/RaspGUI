#ifndef _DRAWER_HPP
#define _DRAWER_HPP

class Drawer
{
public:
    virtual void dispatch_redraw_request() = 0;
};

#endif