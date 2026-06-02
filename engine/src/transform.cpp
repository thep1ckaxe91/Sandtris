#include "transform.hpp"
#include "display.hpp"
#include <algorithm>

namespace sdlgame::transform {

surface::Surface flip(const surface::Surface &surface, bool flip_x,
                      bool flip_y) {
  surface::Surface res = surface;
  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(),
                          res.getTexture())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_RendererFlip flipType = static_cast<SDL_RendererFlip>(
      SDL_FLIP_NONE | (static_cast<int>(flip_x) * SDL_FLIP_HORIZONTAL) |
      (static_cast<int>(flip_y) * SDL_FLIP_VERTICAL));
  if (SDL_RenderCopyEx(sdlgame::display::get_renderer(), surface.getTexture(),
                       nullptr, nullptr, 0, nullptr, flipType))
    printf("Failed to flip\n");
  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}
surface::Surface scale(const surface::Surface &surface, math::Vector2 size) {
  surface::Surface res = surface::Surface(size.x, size.y);
  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(),
                          res.getTexture())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_RenderCopyF(sdlgame::display::get_renderer(), surface.getTexture(),
                  nullptr, nullptr);
  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}

surface::Surface scale_by(const surface::Surface &surface, double factor) {
  return scale(surface, surface.get_size() * factor);
}

/**
 * return a surface that rotated a certain angle counter-clokcwise with passed
 * center angle unit is degrees
 */
surface::Surface rotate(const surface::Surface &surface, double angle_deg,
                        math::Vector2 center) {
  math::Vector2 newtopleft =
      (surface.get_rect().getTopLeft() - center).rotate(angle_deg);
  math::Vector2 newbotleft =
      (surface.get_rect().getBottomLeft() - center).rotate(angle_deg);
  math::Vector2 newtopright =
      (surface.get_rect().getTopRight() - center).rotate(angle_deg);
  math::Vector2 newbotright =
      (surface.get_rect().getBottomRight() - center).rotate(angle_deg);

  surface::Surface res =
      surface::Surface(std::ranges::max({newtopleft.x, newbotleft.x,
                                         newbotright.x, newtopright.x}) -
                           std::ranges::min({newtopleft.x, newbotleft.x,
                                             newbotright.x, newtopright.x}),
                       std::ranges::max({newtopleft.y, newbotleft.y,
                                         newbotright.y, newtopright.y}) -
                           std::ranges::min({newtopleft.y, newbotleft.y,
                                             newbotright.y, newtopright.y}));

  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(),
                          res.getTexture())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }


  SDL_FPoint tmp = {float(center.x), float(center.y)};
  SDL_RenderCopyExF(sdlgame::display::get_renderer(), surface.getTexture(),
                    nullptr, nullptr, angle_deg, &tmp, SDL_FLIP_NONE);
  if (SDL_SetRenderTarget(sdlgame::display::get_renderer(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}
} // namespace sdlgame::transform