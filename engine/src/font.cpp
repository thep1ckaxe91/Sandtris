#include "font.hpp"
#include "color.hpp"
#include "stdio.h"
#include "surface.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

namespace sdlgame::font {
void init() {
  if (TTF_Init()) [[unlikely]] {
    printf("Failed to init font\n%s\n", TTF_GetError());
    exit(1);
  }
  printf("Font successfully initialized\n");
  return;
}
Font::Font(fs::path path, int size) {
  m_height = size;
  auto new_font = TTF_OpenFont(path.c_str(), size);
  if (!new_font) {
    printf("Cant load font\n%s\n", TTF_GetError());
    exit(1);
  }

  m_font.reset(new_font, TTF_CloseFont);
}

/**
 * @return a surface that only contain the text
 * @param antialias = 0 no antialiasing fastest
 *                  = 1 low antialiaing faster
 *                  = 2 high antialiasing slowest
 * the higher, the slower the render will be
 * @param wrap_length in pixel, once the text get over the wrap_length
 * it automatically endline, if it is default = 0,
 * then will only endline when use endline character
 *
 */
sdlgame::surface::Surface Font::render(const std::string &text,
                                       AntiAlias antialias,
                                       sdlgame::color::Color color,
                                       uint32_t wrap_length,
                                       sdlgame::color::Color background) {
  SDL_Surface *surface;
  switch (antialias) {
  case AntiAlias::SOLID:
    surface = TTF_RenderUTF8_Solid_Wrapped(m_font.get(), text.c_str(),
                                           color.to_SDL_Color(), wrap_length);
    break;
  case AntiAlias::SHADED:
    surface = TTF_RenderUTF8_Shaded_Wrapped(m_font.get(), text.c_str(),
                                            color.to_SDL_Color(),
                                            SDL_Color{0, 0, 0, 0}, wrap_length);
    break;
  case AntiAlias::BLENDED:
    surface = TTF_RenderUTF8_Blended_Wrapped(m_font.get(), text.c_str(),
                                             color.to_SDL_Color(), wrap_length);
    break;
  }
  if (surface == nullptr) [[unlikely]] {
    printf("Error render font\n%s\n", TTF_GetError());
    exit(1);
  }
  surface::Surface res = surface::Surface(surface);
  res.fill(background);
  SDL_FreeSurface(surface);
  return res;
}
int Font::get_height() const { return m_height; }

} // namespace sdlgame::font