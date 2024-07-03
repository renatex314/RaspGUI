#include <SDL2/SDL.h>
#include <iostream>
#include "components/app/app.hpp"
#include "uikit/widget/widget.hpp"

int main(int argc, char const *argv[])
{
    App app(800, 600);
    app.run();

    return 0;
}