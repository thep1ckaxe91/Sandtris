#include "event.hpp"
#include "constants.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace sdlgame::event {

static constexpr size_t EVENT_POLL_LIMIT = 50;

static Event tmp;
Event::Event() = default;
Event::Event(SDL_Event e) {
  sdl_event = e;
  type = e.type;
  // TODO: leave these here in case need, now type only is good enough
  // but need refactor for future scale if needed (at that point just move to
  // SDL3)

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

  static std::vector<Event> current_events{EVENT_POLL_LIMIT};
  current_events.clear();

  if (current_events.capacity() < EVENT_POLL_LIMIT) // unlikely?
    current_events.reserve(EVENT_POLL_LIMIT);

  SDL_Event e;
  // while (SDL_PollEvent(&e)) // tried this, but seem like there're problem with event polling limit
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