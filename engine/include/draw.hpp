#pragma once
#ifndef SDLGAME_DRAW_
#define SDLGAME_DRAW_
#include "color.hpp"
#include "rect.hpp"
#include "surface.hpp"

namespace sdlgame::draw {
/**
 * width determine how far the border will expand to the INSIDE
 */
void rect(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
          rect::Rect rect, int width = 0);

void line(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
          double x1, double y1, double x2, double y2);
void line(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
          math::Vector2 start, math::Vector2 end);
void circle(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
            int centerX, int centerY, int radius, int width = 0);
void polygon(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
             std::vector<math::Vector2> points);
void point(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
           double x, double y);
void points(sdlgame::surface::Surface &surface, sdlgame::color::Color color,
            const std::vector<math::Vector2> &points);
} // namespace sdlgame::draw
#endif