#pragma once
#ifndef SDLGAME_COLOR_
#define SDLGAME_COLOR_
#include "SDL2/SDL_pixels.h"
#include <concepts>
#include <cstdint>
#include <string>

namespace sdlgame::color {

void init();
/**
 *  class for color, all values range from [0,255]
 */
class Color {
public:
  uint8_t r, g, b, a;

  Color() = default;
  Color(const std::string &name);

  template <std::convertible_to<uint8_t> Tr, std::convertible_to<uint8_t> Tg,
            std::convertible_to<uint8_t> Tb, std::convertible_to<uint8_t> Ta>
  constexpr Color(Tr _r, Tg _g, Tb _b, Ta _a)
      : r(static_cast<uint8_t>(_r)), g(static_cast<uint8_t>(_g)),
        b(static_cast<uint8_t>(_b)), a(static_cast<uint8_t>(_a)) {}

  template <std::convertible_to<uint8_t> Tr, std::convertible_to<uint8_t> Tg,
            std::convertible_to<uint8_t> Tb>
  constexpr Color(Tr _r, Tg _g, Tb _b)
      : r(static_cast<uint8_t>(_r)), g(static_cast<uint8_t>(_g)),
        b(static_cast<uint8_t>(_b)), a(255) {}

  SDL_Color to_SDL_Color() const;
  /**return Uint32 kind of color*/
  uint32_t toUint32Color() const;
  std::string toString();

  Color operator+(const Color &) const;
  Color operator-(const Color &) const;
  Color operator*(const Color &) const;
  Color operator/(const Color &) const;
  Color operator%(const Color &) const;

  Color operator~() const; // inverse color
};
} // namespace sdlgame::color

#endif
