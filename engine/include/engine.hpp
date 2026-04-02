#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "color.hpp"
#include "constants.hpp"
#include "display.hpp"
#include "draw.hpp"
#include "event.hpp"
#include "font.hpp"
#include "image.hpp"
#include "key.hpp"
#include "math.hpp"
#include "mixer.hpp"
#include "mouse.hpp"
#include "music.hpp"
#include "random.hpp"
#include "rect.hpp"
#include "sprite.hpp"
#include "surface.hpp"
#include "time.hpp"
#include "transform.hpp"
#include <filesystem>
using Event = sdlgame::event::Event;
using Rect = sdlgame::rect::Rect;
using Vector2 = sdlgame::math::Vector2;
using Surface = sdlgame::surface::Surface;
using Color = sdlgame::color::Color;
using Sound = sdlgame::mixer::Sound;
using Channel = sdlgame::mixer::Channel;
using Font = sdlgame::font::Font;

namespace fs = std::filesystem;

namespace sdlgame {
/**
 * @return base path to the exe file that call this function
 */
fs::path get_base_path();
void init();
void quit();
} // namespace sdlgame

#endif