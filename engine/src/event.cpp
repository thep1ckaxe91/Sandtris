#include "event.hpp"
#include "SDL2/SDL_events.h"
#include "constants.hpp"
#include <iostream>
#include <stdexcept>

namespace sdlgame::event {
namespace {
Event tmp;
constexpr int EVENT_POLL_LIMIT = 100;
}
Event::Event() : type(0), timestamp(0) {}
Event::Event(SDL_Event e) : sdl_event(e) {
  type = e.type;
  if (e.type == SDL_KEYDOWN or e.type == SDL_KEYUP) {
    timestamp = e.key.timestamp;
    dict["key"] = e.key.keysym.sym;
    dict["mod"] = e.key.keysym.mod;
    dict["scancode"] = e.key.keysym.scancode;
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

int64_t Event::operator[](std::string key) const {
  if (dict.find(key) != dict.end()) {
    return dict.at(key);
  }
  return -1;
}

std::vector<Event> &get() {
  static std::vector<Event> current_events;
  current_events.clear();

  if (current_events.capacity() < EVENT_POLL_LIMIT) {
    current_events.reserve(EVENT_POLL_LIMIT);
  }

  SDL_Event e;
  for (int i = 0; i < EVENT_POLL_LIMIT; i++) {
    if (!SDL_PollEvent(&e))
      break;
    current_events.push_back(Event(e));
  }
  return current_events;
}

void post(uint32_t event_type) {
  if (event_type <= USEREVENT) {
    std::cerr << "WARNING: Posting non-user event type\n";
  }
  tmp.sdl_event.type = event_type;
  SDL_PushEvent(&tmp.sdl_event);
}
} // namespace sdlgame::event
