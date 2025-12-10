/**
 * @authors thep1ckaxe
 * @contributor: Ngô Hoan Tài and many more from SDL2's developers
 * email: ThePickaxe91@gmail.com
 *
 * @brief this is also a replicate for pygame in c++, but due to some exploitation, redoing and still testing
 *
 * REQUIREMENT: SDL2 installed to your mingw/include directory, SDL_image/mixer/ttf in a folder named SDL3 also in your mingw/include
 *
 * all pixel format is RGBA32, fixed
 *
 * @warning this is not thread-safe, recommend only sigle threading, currently only support window OS
 *
 * @copyright if you want to use this file, please contact for permission, after that, feel free to use and modify this file
 */
#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <bits/stdc++.h>
#include "math.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include "display.hpp"
#include "event.hpp"
#include "time.hpp"
#include "music.hpp"
#include "random.hpp"
#include "font.hpp"
#include "mixer.hpp"
#include "sprite.hpp"
#include "transform.hpp"
#include "draw.hpp"
#include "mouse.hpp"
#include "key.hpp"
#include "color.hpp"
#include "image.hpp"
#include "constants.hpp"
#define null NULL
using Event = sdlgame::event::Event;
using Rect = sdlgame::rect::Rect;
using Vector2 = sdlgame::math::Vector2;
using Surface = sdlgame::surface::Surface;
using Color = sdlgame::color::Color;
using Sound = sdlgame::mixer::Sound;
using Channel = sdlgame::mixer::Channel;
using Font = sdlgame::font::Font;
namespace sdlgame
{
    /**
     * @return base path to the exe file that call this function
     */
    std::string get_base_path();
    void init();
    void quit();
}

#endif