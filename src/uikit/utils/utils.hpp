#include <string>
#include <filesystem>
#include <SDL2/SDL.h>

#ifndef _UTILS_H
#define _UTILS_H

namespace uikit
{
    class Utils
    {
    public:
        static std::string get_application_path();
        static bool file_exists(std::string path);
    };
}

#endif