#ifndef SDLGAME_EVENT_
#define SDLGAME_EVENT_
#include "SDL2/SDL_events.h"
#include <string>
#include <unordered_map>
#include <vector>
namespace sdlgame::event {
/**
 *  class represent a event like keyboard input or mouse click (anything
 * happening in the game)
 */
class Event {
private:
  std::unordered_map<std::string, int64_t> dict; // FIXME: this kind of architecture is hell

public:
  uint32_t type;
  uint32_t timestamp;
  SDL_Event sdl_event;
  Event();
  Event(SDL_Event e);
  int64_t operator[](std::string key);
};
std::vector<Event> &get();
/**please only use this for user event*/
void post(uint32_t event_type);
} // namespace sdlgame::event

#endif