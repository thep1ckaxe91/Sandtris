#ifndef SAND_HPP
#define SAND_HPP
#include <map>
#include "constant.hpp"
using Color = sdlgame::color::Color;
using namespace std;

//Bit shift for color check, not for actual color


extern map<SandShift,Color> SandShiftColor;
struct Sand
{
    SandShift mask;
    Uint8 color_offset_rgb;
    // Uint8 inertia;
    Sand(SandShift mask = EMPTY_SAND);
};

#endif