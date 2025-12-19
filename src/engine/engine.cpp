// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "engine.hpp"

void sdlgame::init()
{
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
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
    // SDL_DestroyWindowSurface(sdlgame::display::window);
    SDL_DestroyRenderer(sdlgame::display::renderer);
    SDL_DestroyWindow(sdlgame::display::window);
    TTF_Quit();
    SDL_Quit();
}
std::string sdlgame::get_base_path()
{
    return std::string(SDL_GetBasePath());
}