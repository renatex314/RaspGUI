#include "app.hpp"

App::App(int width, int height)
{
    this->window_size.width = width;
    this->window_size.height = height;
    this->last_measured_loop_tick = 0;
    this->running = false;
    this->current_event = SDL_Event();
    bool sdl_init_success = this->init_sdl();

    if (!sdl_init_success)
    {
        throw std::runtime_error("Erro ao iniciar o SDL !!!");
    }
}

App::~App()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

bool App::init_sdl()
{
    // Set environment variable to disable compositor bypass imposed by SDL
    putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Erro ao iniciar o SDL: " << SDL_GetError() << std::endl;

        return false;
    }

    SDL_CreateWindowAndRenderer(
        this->window_size.width,
        this->window_size.height,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
        &this->window,
        &this->renderer);

    if (this->window == NULL || this->renderer == NULL)
    {
        std::cout << "Erro ao criar a janela e o renderizador: " << SDL_GetError() << std::endl;

        return false;
    }

    SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    return true;
}

void App::run()
{
    this->run_loop();
}

void App::stop()
{
    this->running = false;
}

void App::run_loop()
{
    Uint32 elapsed_time = 0;
    this->running = true;

    while (this->running)
    {
        this->last_measured_loop_tick = SDL_GetTicks();

        this->handle_events();
        this->run_loop_iteration();

        elapsed_time = SDL_GetTicks() - this->last_measured_loop_tick;
        if (elapsed_time < APP_FPS_DELAY)
        {
            SDL_Delay(APP_FPS_DELAY - elapsed_time);
        }
    }
}

void App::run_loop_iteration()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    SDL_RenderPresent(this->renderer);
}

void App::handle_events()
{
    while (SDL_PollEvent(&this->current_event))
    {
        switch (this->current_event.type)
        {
        case SDL_QUIT:
            this->running = false;
            break;

        case SDL_KEYUP:
            if (this->current_event.key.keysym.sym == SDLK_ESCAPE)
            {
                this->running = false;
            }
            break;

        default:
            break;
        }
    }
}