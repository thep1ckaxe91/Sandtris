#include "surface.hpp"
#include "color.hpp"
#include "display.hpp"
#include "math.hpp"
#include "rect.hpp"
#include "stdio.h"
#include <SDL_error.h>
#include <SDL_render.h>
#include <utility>
namespace sdlgame::surface {

Surface::Surface() { texture = nullptr; }

Surface::Surface(int width, int height) {
  auto new_tex =
      SDL_CreateTexture(display::renderer.get(),
                        SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, width, height);

  if (!new_tex) {
    printf("Failed to create texture\nErr: %s\n", SDL_GetError());
    exit(0);
  }

  texture.reset(new_tex);

  size.x = width;
  size.y = height;
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::renderer.get(), texture.get());
  SDL_SetRenderDrawColor(display::renderer.get(), 0, 0, 0, 0);
  SDL_RenderClear(display::renderer.get());
  SDL_SetRenderTarget(display::renderer.get(), nullptr);
}

Surface::Surface(const Surface &oth) {
  int w, h;

  if (SDL_QueryTexture(oth.texture.get(), nullptr, nullptr, &w, &h))
      [[unlikely]] {
    printf("Failed to query copy target texture\nErr: %s\n", SDL_GetError());
    exit(1);
  }

  auto new_tex = SDL_CreateTexture(display::renderer.get(),
                                   SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h);
  if (new_tex == nullptr) [[unlikely]] {
    printf("Failed to create texture from another Surface object\nErr: %s\n",
           SDL_GetError());
    exit(1);
  }
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::renderer.get(), texture.get());
  SDL_SetRenderDrawColor(display::renderer.get(), 0, 0, 0, 0);
  SDL_RenderClear(display::renderer.get());
  SDL_RenderCopy(display::renderer.get(), oth.texture.get(), nullptr,
                 nullptr);
  SDL_SetRenderTarget(display::renderer.get(), nullptr);
  size.x = w;
  size.y = h;
}

Surface::Surface(Surface &&other) noexcept
    : texture(std::move(other.texture)),
      size(std::exchange(other.size, {0, 0})) {}

Surface::Surface(SDL_Texture *oth) {
  int w, h;
  SDL_QueryTexture(oth, nullptr, nullptr, &w, &h);
  auto new_tex = SDL_CreateTexture(display::renderer.get(),
                                   SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h);
  if (new_tex == nullptr) {
    printf("Failed to create texture from another texture\nErr: %s\n",
           SDL_GetError());
    exit(0);
  }

  texture.reset(new_tex);

  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::renderer.get(), texture.get());
  SDL_SetRenderDrawColor(display::renderer.get(), 0, 0, 0, 0);
  SDL_RenderClear(display::renderer.get());
  SDL_RenderCopy(display::renderer.get(), oth, nullptr, nullptr);
  SDL_SetRenderTarget(display::renderer.get(), nullptr);

  SDL_DestroyTexture(oth);
}

Surface::Surface(SDL_Surface *surf) : size(surf->w, surf->h) {
  auto new_tex = SDL_CreateTextureFromSurface(display::renderer.get(), surf);    
  // printf("tex: %p | surf: %p\n",texture,surf);
  if (!new_tex) {
    printf("Failed to create texture form surface\nErr:%s\n", SDL_GetError());
    exit(1);
  }

  texture.reset(new_tex);
}

Surface &Surface::operator=(const Surface &other) {
  if (!other.texture) [[unlikely]] {
    if (texture) {
      printf("Warning: Copy a null texture.\n");
      texture.reset();
    }
  } else if (this != &other) [[likely]] {
    if (texture != nullptr)
      texture.reset();

    int w, h;
    SDL_QueryTexture(other.texture.get(), nullptr, nullptr, &w, &h);

    auto new_tex =
        SDL_CreateTexture(display::renderer.get(),
                          SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h);
    if (new_tex == nullptr) [[unlikely]] {
      printf("Failed to create texture which assigning\nErr: %s\n",
             SDL_GetError());
      exit(1);
    }
    texture.reset(new_tex);

    SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(display::renderer.get(), texture.get());
    SDL_SetRenderDrawColor(display::renderer.get(), 0, 0, 0, 0);
    SDL_RenderClear(display::renderer.get());
    SDL_RenderCopy(display::renderer.get(), other.texture.get(),
                   nullptr, nullptr);
    SDL_SetRenderTarget(display::renderer.get(), nullptr);
    size = other.size;
  }
  return *this;
}

Surface &Surface::operator=(Surface &&other) noexcept(true) {
  if (this != std::addressof(other)) {
    texture.reset(other.texture.release());
    size = other.size;
  }
  return *this;
}

/**
 * Return a copy of the surface rect
 *
 */
sdlgame::rect::Rect Surface::getRect() const {
  return sdlgame::rect::Rect(0, 0, size.x, size.y);
}
/**
 * Blit a surface onto this surface with position and size, leave size be -1,-1
will be its original size
 * the surface or image will stretch or shrink acoording to the size
 */
void Surface::blit(const Surface &source, sdlgame::math::Vector2 pos,
                   sdlgame::math::Vector2 size, sdlgame::rect::Rect area) {
  if (area == sdlgame::rect::Rect()) {
    area = sdlgame::rect::Rect(0, 0, source.getWidth(), source.getHeight());
  }
  sdlgame::rect::Rect destrect = sdlgame::rect::Rect(
      pos.x, pos.y, (size.x < 0 ? source.getWidth() : size.x),
      (size.y < 0 ? source.getHeight() : size.y));
  if (SDL_SetRenderTarget(display::renderer.get(), texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_Rect srcrect = area.to_SDL_Rect();
  SDL_FRect dstrect = destrect.to_SDL_FRect();
  // printf("src: %p ren: %p \n",source.texture.get(),
  // display::renderer.get());
  if (SDL_RenderCopyF(display::renderer.get(), source.texture.get(),
                      &srcrect, &dstrect)) {
    printf("Error copy texture onto another\n%s\n", SDL_GetError());
    exit(1);
  }
  if (SDL_SetRenderTarget(display::renderer.get(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
}
void Surface::fill(sdlgame::color::Color color) {
  if (SDL_SetRenderTarget(display::renderer.get(), texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }

  if (SDL_SetRenderDrawColor(display::renderer.get(), color.r, color.g,
                             color.b, color.a)) {
    printf("Failed to set draw color\nErr:%s\n", SDL_GetError());
    exit(0);
  }
  if (SDL_RenderClear(display::renderer.get())) {
    printf("Failed to clear the render target\nErr:%s\n", SDL_GetError());
    exit(0);
  }
  if (SDL_SetRenderTarget(display::renderer.get(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
}
sdlgame::math::Vector2 Surface::get_size() const { return size; }
double Surface::getWidth() const { return size.x; }
double Surface::getHeight() const { return size.y; }

} // namespace sdlgame::surface
