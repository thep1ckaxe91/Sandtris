#ifndef SAND_HPP
#define SAND_HPP
#include <array>
#include "constant.hpp"
using Color = sdlgame::color::Color;


//Bit shift for color check, not for actual color

extern std::array<Color, 9> SandShiftColor;

struct Sand // 2 byte expected
{
    SandShift mask; // with enum class, this now become 1 byte
    Uint8 color_offset_rgb;
    // Uint8 inertia;
    Sand(SandShift mask = SandShift::EMPTY_SAND);
};

#endif