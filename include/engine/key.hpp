// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#include "SDL3/SDL_scancode.h"
#include <vector>



namespace sdlgame{
    namespace key
    {
        extern const bool *keyState;
        extern std::vector<bool> keys;
        /**
         *  assume that you called the SDL_PumpEvents function before calling this, this funciton should work fine
         */
        std::vector<bool> &get_pressed();
    }
}