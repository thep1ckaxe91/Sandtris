#pragma once
#ifndef SDLGAME_MOUSE_
#define SDLGAME_MOUSE_
#include <span>
#include "math.hpp"
namespace sdlgame{
    namespace mouse
    {
        math::Vector2 get_pos();
        std::span<const bool, 5> get_pressed();
        math::Vector2 get_rel();
        void set_visible(bool enable);
        bool get_visible();
    }
}

#endif