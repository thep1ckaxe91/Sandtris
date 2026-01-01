#include "key.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keyboard.h"
const Uint8 *sdlgame::key::keyState;
std::vector<bool> sdlgame::key::keys;
std::vector<bool> &sdlgame::key::get_pressed()
{
    int numKeys;
    SDL_PumpEvents();
    keyState = SDL_GetKeyboardState(&numKeys);
    if (keys.size() == 0)
        keys.resize(numKeys);
    for (int i = 0; i < numKeys; ++i)
    {
        keys[i] = keyState[i];
    }
    return keys;
}