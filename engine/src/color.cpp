#include "color.hpp"
#include <SDL_pixels.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <string_view>

namespace sdlgame::color {

constexpr size_t __named_color_size = 144;

struct __NamedColor {
  std::string_view name;
  uint8_t r;
  uint8_t g;
  uint8_t b;

  constexpr __NamedColor(std::string_view _name,
                         std::initializer_list<uint8_t> value)
      : name(_name), r(*value.begin()), g(*(value.begin() + 1)),
        b(*(value.begin() + 2)) {}
};

constexpr std::array<__NamedColor, __named_color_size> __named_color = {{
    {"alice blue", {240, 248, 255}},
    {"antique white", {250, 235, 215}},
    {"aqua", {0, 255, 255}},
    {"aqua marine", {127, 255, 212}},
    {"azure", {240, 255, 255}},
    {"beige", {245, 245, 220}},
    {"bisque", {255, 228, 196}},
    {"black", {0, 0, 0}},
    {"blanched almond", {255, 235, 205}},
    {"blue", {0, 0, 255}},
    {"blue violet", {138, 43, 226}},
    {"brown", {165, 42, 42}},
    {"burly wood", {222, 184, 135}},
    {"cadet blue", {95, 158, 160}},
    {"chartreuse", {127, 255, 0}},
    {"chocolate", {210, 105, 30}},
    {"coral", {255, 127, 80}},
    {"corn flower blue", {100, 149, 237}},
    {"corn silk", {255, 248, 220}},
    {"crimson", {220, 20, 60}},
    {"cyan", {0, 255, 255}},
    {"dark blue", {0, 0, 139}},
    {"dark cyan", {0, 139, 139}},
    {"dark golden rod", {184, 134, 11}},
    {"dark gray", {169, 169, 169}},
    {"dark green", {0, 100, 0}},
    {"dark grey", {169, 169, 169}},
    {"dark khaki", {189, 183, 107}},
    {"dark magenta", {139, 0, 139}},
    {"dark olive green", {85, 107, 47}},
    {"dark orange", {255, 140, 0}},
    {"dark orchid", {153, 50, 204}},
    {"dark red", {139, 0, 0}},
    {"dark salmon", {233, 150, 122}},
    {"dark sea green", {143, 188, 143}},
    {"dark slate blue", {72, 61, 139}},
    {"dark slate gray", {47, 79, 79}},
    {"dark turquoise", {0, 206, 209}},
    {"dark violet", {148, 0, 211}},
    {"deep pink", {255, 20, 147}},
    {"deep sky blue", {0, 191, 255}},
    {"dim gray", {105, 105, 105}},
    {"dim grey", {105, 105, 105}},
    {"dodger blue", {30, 144, 255}},
    {"firebrick", {178, 34, 34}},
    {"floral white", {255, 250, 240}},
    {"forest green", {34, 139, 34}},
    {"fuchsia", {255, 0, 255}},
    {"gainsboro", {220, 220, 220}},
    {"ghost white", {248, 248, 255}},
    {"gold", {255, 215, 0}},
    {"golden rod", {218, 165, 32}},
    {"gray", {128, 128, 128}},
    {"green", {0, 128, 0}},
    {"green yellow", {173, 255, 47}},
    {"grey", {128, 128, 128}},
    {"honeydew", {240, 255, 240}},
    {"hot pink", {255, 105, 180}},
    {"indian red", {205, 92, 92}},
    {"indigo", {75, 0, 130}},
    {"ivory", {255, 255, 240}},
    {"khaki", {240, 230, 140}},
    {"lavender", {230, 230, 250}},
    {"lavender blush", {255, 240, 245}},
    {"lawn green", {124, 252, 0}},
    {"lemon chiffon", {255, 250, 205}},
    {"light blue", {173, 216, 230}},
    {"light coral", {240, 128, 128}},
    {"light cyan", {224, 255, 255}},
    {"light golden rod yellow", {250, 250, 210}},
    {"light gray", {211, 211, 211}},
    {"light green", {144, 238, 144}},
    {"light grey", {211, 211, 211}},
    {"light pink", {255, 182, 193}},
    {"light salmon", {255, 160, 122}},
    {"light sea green", {32, 178, 170}},
    {"light sky blue", {135, 206, 250}},
    {"light slate gray", {119, 136, 153}},
    {"light steel blue", {176, 196, 222}},
    {"light yellow", {255, 255, 224}},
    {"lime", {0, 255, 0}},
    {"lime green", {50, 205, 50}},
    {"linen", {250, 240, 230}},
    {"magenta", {255, 0, 255}},
    {"maroon", {128, 0, 0}},
    {"medium aqua marine", {102, 205, 170}},
    {"medium blue", {0, 0, 205}},
    {"medium orchid", {186, 85, 211}},
    {"medium purple", {147, 112, 219}},
    {"medium sea green", {60, 179, 113}},
    {"medium slate blue", {123, 104, 238}},
    {"medium spring green", {0, 250, 154}},
    {"medium turquoise", {72, 209, 204}},
    {"medium violet red", {199, 21, 133}},
    {"midnight blue", {25, 25, 112}},
    {"mint cream", {245, 255, 250}},
    {"misty rose", {255, 228, 225}},
    {"moccasin", {255, 228, 181}},
    {"navajo white", {255, 222, 173}},
    {"navy", {0, 0, 128}},
    {"old lace", {253, 245, 230}},
    {"olive", {128, 128, 0}},
    {"olive drab", {107, 142, 35}},
    {"orange", {255, 165, 0}},
    {"orange red", {255, 69, 0}},
    {"orchid", {218, 112, 214}},
    {"pale golden rod", {238, 232, 170}},
    {"pale green", {152, 251, 152}},
    {"pale turquoise", {175, 238, 238}},
    {"pale violet red", {219, 112, 147}},
    {"papaya whip", {255, 239, 213}},
    {"peach puff", {255, 218, 185}},
    {"peru", {205, 133, 63}},
    {"pink", {255, 192, 203}},
    {"plum", {221, 160, 221}},
    {"powder blue", {176, 224, 230}},
    {"purple", {128, 0, 128}},
    {"red", {255, 0, 0}},
    {"rosy brown", {188, 143, 143}},
    {"royal blue", {65, 105, 225}},
    {"saddle brown", {139, 69, 19}},
    {"salmon", {250, 128, 114}},
    {"sandy brown", {244, 164, 96}},
    {"sea green", {46, 139, 87}},
    {"sea shell", {255, 245, 238}},
    {"sienna", {160, 82, 45}},
    {"silver", {192, 192, 192}},
    {"sky blue", {135, 206, 235}},
    {"slate blue", {106, 90, 205}},
    {"slate gray", {112, 128, 144}},
    {"snow", {255, 250, 250}},
    {"spring green", {0, 255, 127}},
    {"steel blue", {70, 130, 180}},
    {"tan", {210, 180, 140}},
    {"teal", {0, 128, 128}},
    {"thistle", {216, 191, 216}},
    {"tomato", {255, 99, 71}},
    {"turquoise", {64, 224, 208}},
    {"violet", {238, 130, 238}},
    {"wheat", {245, 222, 179}},
    {"white", {255, 255, 255}},
    {"white smoke", {245, 245, 245}},
    {"yellow", {255, 255, 0}},
    {"yellow green", {154, 205, 50}},
}};

static void to_lowercase(std::string &str) {
  std::ranges::transform(str, str.begin(),
                         [](unsigned char c) { return std::tolower(c); });
}

Color::Color(const std::string &p_name) : a(255) {
  auto name = p_name;
  to_lowercase(name);
  if (name == "none" || name.size() == 0) {
    r = g = b = a = 0;
    return;
  }

  auto it =
      std::ranges::lower_bound(__named_color, name, {}, &__NamedColor::name);

  if (it != __named_color.end() && it->name == name) [[likely]] {
    r = it->r;
    g = it->g;
    b = it->b;
  } else [[unlikely]] {
    std::cerr << "Unrecognize color identifier: " << p_name << '\n';
    exit(1);
  }
}

Color Color::operator+(const Color &oth) const {
  return {r + oth.r, g + oth.g, b + oth.b, a + oth.a};
}
Color Color::operator-(const Color &oth) const {
  return {r - oth.r, g - oth.g, b - oth.b, a - oth.a};
}
Color Color::operator*(const Color &oth) const {
  return {r * oth.r, g * oth.g, b * oth.b, a * oth.a};
}
Color Color::operator/(const Color &oth) const {
  return {r / oth.r, g / oth.g, b / oth.b, a / oth.a};
}
Color Color::operator%(const Color &oth) const {
  return {r % oth.r, g % oth.g, b % oth.b, a % oth.a};
}

Color Color::operator~() const { return {255 - r, 255 - g, 255 - b, a}; }

SDL_Color Color::to_SDL_Color() const { return SDL_Color{r, g, b, a}; }
/**return uint32_t kind of color with RGBA format*/
uint32_t Color::toUint32Color() const {
  static SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
  return SDL_MapRGBA(format, r, g, b, a);
}
std::string Color::toString() {
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "Color(%d,%d,%d,%d)", r, g, b, a);
  return std::string(buffer);
}
} // namespace sdlgame::color
