// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "image.hpp"
#include "surface.hpp"
#include "display.hpp"
#include <stdio.h>
#include <string>

void sdlgame::image::init()
{
    // IMG_Init is not needed in SDL3_image
}
// sdlgame::surface::Surface img_transfer_surf;
sdlgame::surface::Surface sdlgame::image::load(const std::string path)
{
    SDL_Texture *tex = IMG_LoadTexture(sdlgame::display::renderer, path.c_str());
    if (tex == NULL)
    {
        SDL_Log("Cant load image\n%s\n", IMG_GetError());
        exit(0);
    }
    // img_transfer_surf =sdlgame::surface::Surface(tex);
    return sdlgame::surface::Surface(tex);
}