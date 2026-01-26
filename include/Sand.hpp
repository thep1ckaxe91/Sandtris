#ifndef SAND_HPP
#define SAND_HPP
#include <array>
#include "constant.hpp"
using Color = sdlgame::color::Color;


//Bit shift for color check, not for actual color

extern std::array<Color, 9> SandShiftColor;

struct Sand
{
    SandShift mask;
    Uint8 color_offset_rgb;
    // Uint8 inertia;
    Sand(SandShift mask = EMPTY_SAND);
};

#endif