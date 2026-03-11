#include "engine.hpp"

void sdlgame::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(0);
    }
    else
    {
        printf("SDL successfully initialized\n");
    }
    sdlgame::image::init();
    sdlgame::font::init();
}
void sdlgame::quit()
{
    sdlgame::display::renderer.reset();
    sdlgame::display::window.reset();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
std::string sdlgame::get_base_path()
{
    return std::string(SDL_GetBasePath());
}