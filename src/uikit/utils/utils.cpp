#include "utils.hpp"

using namespace uikit;

std::string Utils::get_application_path()
{
    char *path = SDL_GetBasePath();
    std::string application_path(path);
    SDL_free(path);

    return application_path;
}

bool Utils::file_exists(std::string path)
{
    return std::filesystem::exists(path);
}