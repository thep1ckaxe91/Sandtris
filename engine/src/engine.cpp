#include "engine.hpp"
#include "key.hpp"
#include <SDL_image.h>


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
    sdlgame::key::init();
}
void sdlgame::quit()
{
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
fs::path sdlgame::get_base_path()
{
    static fs::path p;
    if (p.empty()){
        char* base_path = SDL_GetBasePath();
        if (!base_path) p = fs::path("./");
        else p = base_path;
        SDL_free(base_path);
    }
    return p;
}