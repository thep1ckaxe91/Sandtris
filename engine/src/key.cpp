#include "key.hpp"

#include "SDL2/SDL_keyboard.h"

namespace sdlgame::key {

const uint8_t *get_pressed() {
  static int numKeys;
  static const uint8_t *keyState = SDL_GetKeyboardState(&numKeys);

  return keyState;
}
} // namespace sdlgame::key