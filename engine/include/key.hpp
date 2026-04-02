#ifndef SDLGAME_KEY_
#define SDLGAME_KEY_

#include <cstdint>

namespace sdlgame::key {
/**
 *  assume that you called the SDL_PumpEvents function before calling this, this
 * funciton should work fine
 */
const uint8_t *get_pressed();
} // namespace sdlgame::key
  // namespace sdlgame
#endif