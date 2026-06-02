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

Surface::Surface(int width, int height) {
  texture.reset(SDL_CreateTexture(display::get_renderer(),
                                  SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, width,
                                  height));

  if (!texture) {
    printf("Failed to create texture\nErr: %s\n", SDL_GetError());
    exit(0);
  }

  size.x = width;
  size.y = height;
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::get_renderer(), texture.get());
  SDL_SetRenderDrawColor(display::get_renderer(), 0, 0, 0, 0);
  SDL_RenderClear(display::get_renderer());
  SDL_SetRenderTarget(display::get_renderer(), nullptr);
}

Surface::Surface(const Surface &oth) {
  int w, h;

  if (SDL_QueryTexture(oth.getTexture(), nullptr, nullptr, &w, &h))
      [[unlikely]] {
    printf("Failed to query copy target texture\nErr: %s\n", SDL_GetError());
    exit(1);
  }

  texture.reset(SDL_CreateTexture(display::get_renderer(),
                                  SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h));
  if (texture == nullptr) [[unlikely]] {
    printf("Failed to create texture from another Surface object\nErr: %s\n",
           SDL_GetError());
    exit(1);
  }
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::get_renderer(), texture.get());
  SDL_SetRenderDrawColor(display::get_renderer(), 0, 0, 0, 0);
  SDL_RenderClear(display::get_renderer());
  SDL_RenderCopy(display::get_renderer(), oth.getTexture(), nullptr,
                 nullptr);
  SDL_SetRenderTarget(display::get_renderer(), nullptr);
  size.x = w;
  size.y = h;
}

Surface::Surface(Surface &&other) noexcept
    : texture(std::move(other.texture)),
      size(std::exchange(other.size, {0, 0})) {}

Surface::Surface(SDL_Texture *oth) {
  sdlgame::memory::SDLUniquePtr<SDL_Texture> old_tex(oth);
  int w, h;
  SDL_QueryTexture(old_tex.get(), nullptr, nullptr, &w, &h);
  texture.reset(SDL_CreateTexture(display::get_renderer(),
                                  SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h));
  if (texture == nullptr) {
    printf("Failed to create texture from another texture\nErr: %s\n",
           SDL_GetError());
    exit(0);
  }

  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(display::get_renderer(), texture.get());
  SDL_SetRenderDrawColor(display::get_renderer(), 0, 0, 0, 0);
  SDL_RenderClear(display::get_renderer());
  SDL_RenderCopy(display::get_renderer(), old_tex.get(), nullptr, nullptr);
  SDL_SetRenderTarget(display::get_renderer(), nullptr);
}

Surface::Surface(SDL_Surface *surf) : size(surf->w, surf->h) {
  texture.reset(SDL_CreateTextureFromSurface(display::get_renderer(), surf));
  // printf("tex: %p | surf: %p\n",texture,surf);
  if (!texture) {
    printf("Failed to create texture form surface\nErr:%s\n", SDL_GetError());
    exit(1);
  }
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
    SDL_QueryTexture(other.getTexture(), nullptr, nullptr, &w, &h);

    auto new_tex =
        SDL_CreateTexture(display::get_renderer(),
                          SDL_PIXELFORMAT_RGBA32, SURFACE_TYPE, w, h);
    if (new_tex == nullptr) [[unlikely]] {
      printf("Failed to create texture which assigning\nErr: %s\n",
             SDL_GetError());
      exit(1);
    }
    texture.reset(new_tex);

    SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(display::get_renderer(), texture.get());
    SDL_SetRenderDrawColor(display::get_renderer(), 0, 0, 0, 0);
    SDL_RenderClear(display::get_renderer());
    SDL_RenderCopy(display::get_renderer(), other.getTexture(),
                   nullptr, nullptr);
    SDL_SetRenderTarget(display::get_renderer(), nullptr);
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
rect::Rect Surface::get_rect() const { return rect::Rect(0, 0, size.x, size.y); }
SDL_Texture *Surface::getTexture() const { return texture.get(); }
/**
 * Blit a surface onto this surface with position and size, leave size be -1,-1
will be its original size
 * the surface or image will stretch or shrink acoording to the size
 */
void Surface::blit(const Surface &source, math::Vector2 pos,
                   math::Vector2 size, rect::Rect area) {
  if (area == rect::Rect()) {
    area = rect::Rect(0, 0, source.get_width(), source.get_height());
  }
  rect::Rect destrect = rect::Rect(
      pos.x, pos.y, (size.x < 0 ? source.get_width() : size.x),
      (size.y < 0 ? source.get_height() : size.y));
  if (SDL_SetRenderTarget(display::get_renderer(), texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_Rect srcrect = area.to_SDL_Rect();
  SDL_FRect dstrect = destrect.to_SDL_FRect();
  // printf("src: %p ren: %p \n",source.getTexture(),
  // display::get_renderer());
  if (SDL_RenderCopyF(display::get_renderer(), source.getTexture(),
                      &srcrect, &dstrect)) {
    printf("Error copy texture onto another\n%s\n", SDL_GetError());
    exit(1);
  }
  if (SDL_SetRenderTarget(display::get_renderer(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
}
void Surface::fill(sdlgame::color::Color color) {
  if (SDL_SetRenderTarget(display::get_renderer(), texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }

  if (SDL_SetRenderDrawColor(display::get_renderer(), color.r, color.g,
                             color.b, color.a)) {
    printf("Failed to set draw color\nErr:%s\n", SDL_GetError());
    exit(0);
  }
  if (SDL_RenderClear(display::get_renderer())) {
    printf("Failed to clear the render target\nErr:%s\n", SDL_GetError());
    exit(0);
  }
  if (SDL_SetRenderTarget(display::get_renderer(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
}
math::Vector2 Surface::get_size() const { return size; }
double Surface::get_width() const { return size.x; }
double Surface::get_height() const { return size.y; }

} // namespace sdlgame::surface
