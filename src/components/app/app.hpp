#include <SDL2/SDL.h>
#include <iostream>

#ifndef _APP_H
#define _APP_H

// 1000 ms / 60 fps = 16 ms
#define APP_FPS_DELAY 16

struct WindowSize
{
    int width;
    int height;
};

class App
{
public:
    App(int width, int height);
    ~App();
    void run();
    void stop();

private:
    bool running;
    Uint32 last_measured_loop_tick;
    SDL_Event current_event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *window_surface;
    struct WindowSize window_size;

    void run_loop();
    void run_loop_iteration();
    void handle_events();
    bool init_sdl();
};

#endif