#include "key.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keyboard.h"

namespace sdlgame::key {
const Uint8 *keyState;
std::vector<bool> keys;
std::vector<bool> &get_pressed() {
  int numKeys;
  SDL_PumpEvents();
  keyState = SDL_GetKeyboardState(&numKeys);
  if (keys.size() == 0)
    keys.resize(numKeys);
  for (int i = 0; i < numKeys; ++i) {
    keys[i] = keyState[i];
  }
  return keys;
}
} // namespace sdlgame::key