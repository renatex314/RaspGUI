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

    uikit::Context *ui_context = new uikit::Context(this->renderer);
    this->ui_manager = new uikit::Manager(ui_context);
    this->simple_widget = new SimpleWidget(this->ui_manager);
    this->simple_widget->set_margin_bottom(100);

    this->test_widget = new uikit::WidgetGroup(this->ui_manager);

    this->ui_manager->attach_root(this->test_widget);

    delete ui_context;
}

App::~App()
{
    delete this->ui_manager;
    delete this->simple_widget;
    delete this->test_widget;
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

    if (TTF_Init() < 0)
    {
        std::cout << "Erro ao iniciar o SDL TTF: " << TTF_GetError() << std::endl;

        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_CreateWindowAndRenderer(
        this->window_size.width,
        this->window_size.height,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI,
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
    this->ui_manager->render();
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
    this->ui_manager->render();
}

void App::handle_events()
{
    while (SDL_PollEvent(&this->current_event))
    {
        switch (this->current_event.type)
        {
        case SDL_WINDOWEVENT:
            if (this->current_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                this->ui_manager->dispatch_redraw_request();
            }
            break;

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

        this->ui_manager->handle_event(this->current_event);
    }
}