#ifndef SDLGAME_FONT_
#define SDLGAME_FONT_
#include "SDL2/SDL_ttf.h"
#include "memory.hpp"
#include "surface.hpp"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace sdlgame::font {

enum class AntiAlias {
  SOLID,
  SHADED,
  BLENDED
};

/**
 * @brief initialize font, after call this function, you should be able to use
 * other function and class
 */
void init();
class Font {
public:
  Font(fs::path path, int size = 12);
  Font();
  Font(const Font &) = default;
  Font(Font &&) = default;
  Font &operator=(Font &&) = default;
  Font &operator=(const Font &) = default;

  /**
   * @return a surface that only contain the text
   * @param antialias = 0 no antialiasing fastest
   *                  = 1 low antialiaing faster
   *                  = 2 high antialiasing slowest
   * the higher, the slower the render will be
   * @param wrap_length in pixel, once the text get over the wrap_length
   * it automatically endline, if it is default = 0,
   * then will only endline when use endline character
   */
  sdlgame::surface::Surface
  render(const std::string text, AntiAlias antialias, sdlgame::color::Color color,
         uint32_t wrap_length = 0,
         sdlgame::color::Color background = sdlgame::color::Color(0, 0, 0, 0));
  // Get the height of the font in pixel
  int get_height() const;

private:
  memory::SDLSharedPtr<TTF_Font> font;
  int height;
};

} // namespace sdlgame::font
#endif