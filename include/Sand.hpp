#pragma once
#ifndef SAND_HPP
#define SAND_HPP
#include "constant.hpp"
#include <array>

// Bit shift for color check, not for actual color

extern std::array<sdlgame::color::Color, 9> SandShiftColor;

struct Sand // 2 byte expected
{
  SandShift mask; // with enum class, this now become 1 byte
  Uint8 color_offset_rgb;
  // Uint8 inertia;
  Sand(SandShift mask = SandShift::EMPTY_SAND);
};

#endif