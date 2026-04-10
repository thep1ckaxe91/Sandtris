#ifndef SDLGAME_SURFACE_
#define SDLGAME_SURFACE_
#include "color.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "rect.hpp"
#define SURFACE_TYPE                                                           \
  SDL_TEXTUREACCESS_TARGET // FIXME: This is very discouraged, please fix in the
                           // future when the stage come
                           // This could be fix with template?

// template<SDL_TextureAccess SurfType> ??
// TMP book might be helpful, check it out first before refactor this for
// template implementation
namespace sdlgame::surface {
/**
 * @brief since the problem mostly related to the heavy draw and surface manage
 * in pygame this module is mostly focus optimizing the surface class, the
 * texture pointer should be null if the surface is represent window after
 * set_mode is called
 */
class Surface {
private:
  sdlgame::memory::SDLUniquePtr<SDL_Texture> texture;

public:
  math::Vector2 size;

  Surface() = default;
  Surface(Surface &&) noexcept;
  Surface(int width, int height);
  Surface(const Surface &oth);
  Surface(SDL_Texture *oth);
  Surface(SDL_Surface *surf);
  Surface &operator=(const Surface &other);
  Surface &operator=(Surface &&) noexcept;
  /**
   * Return a copy of the surface rect
   */
  rect::Rect get_rect() const;
  SDL_Texture *getTexture() const;
  /**
   * Blit a surface onto this surface with position and size, leave size be
   * -1,-1 will be its original size the surface or image will stretch or shrink
   * acoording to the size
   */
  void blit(const Surface &source, math::Vector2 pos,
            math::Vector2 size = math::Vector2(-1, -1),
            rect::Rect area = rect::Rect());
  void fill(sdlgame::color::Color color);
  math::Vector2 get_size() const;
  double get_width() const;
  double get_height() const;
  ~Surface() = default;
};
} // namespace sdlgame::surface

#endif