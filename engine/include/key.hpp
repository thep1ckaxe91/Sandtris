#ifndef SDLGAME_KEY_
#define SDLGAME_KEY_

#include <cstdint>
#include <span>

namespace sdlgame::key {

// Made sure to call this after SDL init
void init();

std::span<const uint8_t> get_pressed();
} // namespace sdlgame::key
  // namespace sdlgame
#endif