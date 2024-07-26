#include <string>

#ifndef _ASSETS_HANDLER_H
#define _ASSETS_HANDLER_H

namespace uikit
{
    class AssetsHandler
    {
    public:
        virtual std::string get_resource_path(std::string resource_name) = 0;
    };
};

#endif