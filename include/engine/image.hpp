// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "SDL3_image/SDL_image.h"
#include "surface.hpp"
#include <string>
namespace sdlgame{
    namespace image
    {
        /**
         * Currently only support JPG and PNG type
         */
        void init();
        /**
         * load an image from file path, require you to create the window object first
        */
        sdlgame::surface::Surface load(std::string path);
    }
}