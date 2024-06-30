#include <SDL2/SDL.h>
#include <iostream>
#include "uikit/widget/widget.hpp"

int main(int argc, char const *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Erro ao iniciar o SDL: " << SDL_GetError() << std::endl;

        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("janela", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    SDL_Event e;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }

            if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}