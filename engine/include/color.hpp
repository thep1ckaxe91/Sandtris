#ifndef SDLGAME_COLOR_
#define SDLGAME_COLOR_
#include "SDL2/SDL_pixels.h"
#include <cstdint>
#include <string>

namespace sdlgame::color {
struct __NamedColor;

constexpr size_t __named_color_size = 144;

extern const std::array<__NamedColor, __named_color_size> __named_color;
void init();
/**
 *  class for color, all values range from [0,255]
 */
class Color {
public:
  uint8_t r, g, b, a;
  Color() = default;
  Color(std::string name);
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

  SDL_Color to_SDL_Color() const;
  /**return Uint32 kind of color*/
  uint32_t toUint32Color() const;
  std::string toString();
  /**
   * @brief add r g b value to the current color, the value will be clamp in
   * range 0,255
   *
   * @param r add red value
   * @param g add green
   * @param b add blue
   * @return Color that have the value of original red + r ...
   */
  Color add_value(uint8_t r, uint8_t g, uint8_t b);
};
} // namespace sdlgame::color

#endif
