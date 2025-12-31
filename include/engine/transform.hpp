#pragma once
#ifndef SDLGAME_TRANSFORM_
#define SDLGAME_TRANSFORM_
#include "surface.hpp"
#include <algorithm>
namespace sdlgame
{
    namespace transform
    {
        /**
         * @return a flipped image in certain axis
         * @param surface source surface
         * @param flip_x whether to flip x or not
         * @param flip_y whether to flip y or not
         */
        sdlgame::surface::Surface flip(sdlgame::surface::Surface surface, bool flip_x, bool flip_y);
        sdlgame::surface::Surface scale(sdlgame::surface::Surface surface, sdlgame::math::Vector2 size);

        sdlgame::surface::Surface scale_by(sdlgame::surface::Surface surface, double factor);

        /**
         * return a surface that rotated a certain angle counter-clokcwise with passed center
         * angle unit is degrees
         */
        sdlgame::surface::Surface rotate(sdlgame::surface::Surface surface, double angle_deg, sdlgame::math::Vector2 center);
    }
}

#endif
