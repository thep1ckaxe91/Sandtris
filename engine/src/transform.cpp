#include "transform.hpp"
#include "display.hpp"

namespace sdlgame::transform {

sdlgame::surface::Surface flip(sdlgame::surface::Surface surface, bool flip_x,
                               bool flip_y) {
  sdlgame::surface::Surface res = surface;
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(),
                          res.texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_RendererFlip flipType = static_cast<SDL_RendererFlip>(
      SDL_FLIP_NONE | (static_cast<int>(flip_x) * SDL_FLIP_HORIZONTAL) |
      (static_cast<int>(flip_y) * SDL_FLIP_VERTICAL));
  if (SDL_RenderCopyEx(sdlgame::display::renderer.get(), surface.texture.get(),
                       nullptr, nullptr, 0, nullptr, flipType))
    printf("Failed to flip\n");
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}
sdlgame::surface::Surface scale(sdlgame::surface::Surface surface,
                                sdlgame::math::Vector2 size) {
  sdlgame::surface::Surface res = sdlgame::surface::Surface(size.x, size.y);
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(),
                          res.texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_RenderCopyF(sdlgame::display::renderer.get(), surface.texture.get(),
                  nullptr, nullptr);
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}

sdlgame::surface::Surface scale_by(sdlgame::surface::Surface surface,
                                   double factor) {
  return scale(surface, surface.get_size() * factor);
}

/**
 * return a surface that rotated a certain angle counter-clokcwise with passed
 * center angle unit is degrees
 * TODO: calculate the new size for the res surface
 */
sdlgame::surface::Surface rotate(sdlgame::surface::Surface surface,
                                 double angle_deg,
                                 sdlgame::math::Vector2 center) {
  sdlgame::math::Vector2 newtopleft =
      (surface.getRect().getTopLeft() - center).rotate(angle_deg);
  sdlgame::math::Vector2 newbotleft =
      (surface.getRect().getBottomLeft() - center).rotate(angle_deg);
  sdlgame::math::Vector2 newtopright =
      (surface.getRect().getTopRight() - center).rotate(angle_deg);
  sdlgame::math::Vector2 newbotright =
      (surface.getRect().getBottomRight() - center).rotate(angle_deg);

  sdlgame::surface::Surface res = sdlgame::surface::Surface(
      std::max({newtopleft.x, newbotleft.x, newbotright.x, newtopright.x}) -
          std::min({newtopleft.x, newbotleft.x, newbotright.x, newtopright.x}),
      std::max({newtopleft.y, newbotleft.y, newbotright.y, newtopright.y}) -
          std::min({newtopleft.y, newbotleft.y, newbotright.y, newtopright.y}));
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(),
                          res.texture.get())) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  SDL_FPoint tmp = {float(center.x), float(center.y)};
  SDL_RenderCopyExF(sdlgame::display::renderer.get(), surface.texture.get(),
                    nullptr, nullptr, angle_deg, &tmp, SDL_FLIP_NONE);
  if (SDL_SetRenderTarget(sdlgame::display::renderer.get(), nullptr)) {
    printf("Failed to set target: %s\n", SDL_GetError());
  }
  return res;
}
} // namespace sdlgame::transform