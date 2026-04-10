#include "key.hpp"

#include "SDL2/SDL_keyboard.h"
#include <cassert>
#include <iostream>

namespace sdlgame::key {
static int numKeys = 0;
static const uint8_t *keyState = nullptr;

void init() {
  keyState = SDL_GetKeyboardState(&numKeys);

  if (!keyState) {
    std::cerr << "Keyboard state pointer is null post-initialization\nDid you "
                 "call this after SDL init?\n";
    exit(1);
  }
}

inline std::span<const uint8_t> get_pressed() {
  assert(keyState != nullptr && "sdlgame::key::init() was never called\n");
  return {keyState, static_cast<size_t>(numKeys)};
}
} // namespace sdlgame::key