#include "event.hpp"
#include <stdexcept>
#include <string>
#include <vector>

namespace sdlgame::event {

std::vector<Event> current_events;

Event tmp;
Event::Event() = default;
Event::Event(SDL_Event e) {
  tmp_e = e;
  type = e.type;
  // TODO: leave these here in case need, now type only is good enough
  // but need refactor for future scale if needed (at that point just move to SDL3)

  if (e.type == SDL_WINDOWEVENT) {
    timestamp = e.window.timestamp;
    dict["windowID"] = e.window.windowID; /**< The associated window */
    dict["event"] = e.window.event;
  } else if (e.type == SDL_KEYDOWN or e.type == SDL_KEYUP) {
    timestamp = e.key.timestamp;
    dict["key"] = e.key.keysym.scancode;
  } else if (e.type == SDL_QUIT) {
    // lol, just here to write const event
  } else if (e.type == SDL_MOUSEWHEEL) {
    timestamp = e.wheel.timestamp;
    dict["x"] = e.wheel.x;
    dict["y"] = e.wheel.y;
  } else if (e.type == SDL_MOUSEBUTTONUP or e.type == SDL_MOUSEBUTTONDOWN) {
    timestamp = e.button.timestamp;
    dict["button"] = e.button.button;
    dict["x"] = e.button.x;
    dict["y"] = e.button.y;
  } else if (e.type == SDL_MOUSEMOTION) {
    timestamp = e.motion.timestamp;
    dict["x"] = e.motion.x;
    dict["y"] = e.motion.y;
    dict["xrel"] = e.motion.xrel;
    dict["yrel"] = e.motion.yrel;
  }
}
int64_t Event::operator[](std::string key) {
  if (dict.find(key) != dict.end()) {
    return dict[key];
  } else {
    throw std::invalid_argument("There's no such key: " + key);
  }
}
std::vector<Event> &get() {
  current_events.clear();
  SDL_Event e;
  // while (SDL_PollEvent(&e))
  for (int i = 1; i <= 30; i++) {
    if (!SDL_PollEvent(&e))
      break;
    current_events.push_back(Event(e));
  }
  return current_events;
}
// please only use this for user event
void post(Uint32 event_type) {
  tmp.tmp_e.type = event_type;
  SDL_PushEvent(&tmp.tmp_e);
}
} // namespace sdlgame::event