#pragma once
#ifndef SDLGAME_DRAW_
#define SDLGAME_DRAW_
#include "surface.hpp"
#include "display.hpp"
#include "color.hpp"
#include "stdio.h"
#include "rect.hpp"
#include <bits/stdc++.h>
namespace sdlgame{
    namespace draw
    {
        /**
         * width determine how far the border will expand to the INSIDE
         */
        void rect(sdlgame::surface::Surface &surface, sdlgame::color::Color color, sdlgame::rect::Rect rect, int width = 0);

        void line(sdlgame::surface::Surface &surface, sdlgame::color::Color color, double x1, double y1, double x2, double y2);
        void line(sdlgame::surface::Surface &surface, sdlgame::color::Color color, sdlgame::math::Vector2 start, sdlgame::math::Vector2 end);
        void circle(sdlgame::surface::Surface &surface, sdlgame::color::Color color, int centerX, int centerY, int radius, int width = 0);
        void polygon(sdlgame::surface::Surface &surface, sdlgame::color::Color color, std::vector<sdlgame::math::Vector2> points);
        void point(sdlgame::surface::Surface &surface, sdlgame::color::Color color, double x, double y);
        void points(sdlgame::surface::Surface &surface, sdlgame::color::Color color,const std::vector<sdlgame::math::Vector2> &points);
    }
}

#endif