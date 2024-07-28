#include "simple_widget.hpp"

using namespace uikit;

SimpleWidget::SimpleWidget(Context *context) : Widget(context)
{
    this->set_width(800);
    this->set_height(600);
    this->bg_intensity = 100;
    this->is_mouse_down = false;
    this->mouse_x = 0;
    this->mouse_y = 0;

    this->font = TTF_OpenFont(context->get_assets_handler()->get_resource_path("jetbrains-mono-regular.ttf").c_str(), 32);
    this->running_thread = SDL_CreateThread(SimpleWidget::redraw_timer, "redraw-thread", this);
}

SimpleWidget::~SimpleWidget()
{
    pthread_cancel(SDL_GetThreadID(this->running_thread));
}

int SDLCALL SimpleWidget::redraw_timer(void *data)
{
    SimpleWidget *widget = (SimpleWidget *)data;

    while (true)
    {
        SDL_Delay(1000 / 60);
        widget->dispatch_redraw_request();
    }

    return 0;
}

// Draws the text in the middle of the screen
void SimpleWidget::draw_current_time(SDL_Renderer *renderer)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[256];
    sprintf(buffer, "%02d:%02d:%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(this->font, buffer, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    SDL_Rect dstrect = {this->get_width() / 2 - text_width / 2, this->get_height() / 2 - text_height / 2, text_width, text_height};
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void SimpleWidget::perform_draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    this->draw_current_time(renderer);
}

void SimpleWidget::on_mouse_down(event::mouse::MouseEvent event)
{
    this->is_mouse_down = true;
    this->bg_intensity = 100;
    this->dispatch_redraw_request();
}

void SimpleWidget::on_mouse_move(event::mouse::MouseEvent event)
{
    this->mouse_x = event.x;
    this->mouse_y = event.y;

    if (!this->is_mouse_down)
    {
        this->bg_intensity = (event.x / 800.0) * 200.0;
        this->dispatch_redraw_request();
    }
}

void SimpleWidget::on_mouse_up(event::mouse::MouseEvent event)
{
    this->is_mouse_down = false;
    this->bg_intensity = 200;
    this->dispatch_redraw_request();
}

void SimpleWidget::on_key_up(event::keyboard::KeyEvent event)
{
    std::cout << "Widget received key Up: " << event.sdl_key_code << std::endl;
}