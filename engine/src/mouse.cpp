#include "mouse.hpp"
#include "display.hpp"
#include "math.hpp"
#include <SDL2/SDL.h>

namespace sdlgame::mouse {

math::Vector2 get_pos() {
  int win_x, win_y;
  SDL_GetMouseState(&win_x, &win_y);
  float logicalX, logicalY;

  SDL_RenderWindowToLogical(display::get_renderer(), win_x, win_y, &logicalX,
                            &logicalY);

  return {logicalX, logicalY};
}
std::span<const bool, 5> get_pressed() {
  static std::array<bool, 5> inputState;
  uint32_t buttonState = SDL_GetMouseState(nullptr, nullptr);
  inputState[0] = (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
  inputState[1] = (buttonState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
  inputState[2] = (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
  inputState[3] = (buttonState & SDL_BUTTON(SDL_BUTTON_X1)) != 0;
  inputState[4] = (buttonState & SDL_BUTTON(SDL_BUTTON_X2)) != 0;
  return inputState;
}
math::Vector2 get_rel() {
  int x, y;
  SDL_GetRelativeMouseState(&x, &y);
  return {static_cast<double>(x), static_cast<double>(y)};
}
void set_visible(bool enable) {
  SDL_ShowCursor(enable ? SDL_ENABLE : SDL_DISABLE);
}
bool get_visible() { return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE; }
} // namespace sdlgame::mouse