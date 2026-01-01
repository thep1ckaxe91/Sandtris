#include "event.hpp"
#include <vector>
#include <string>
#include <stdexcept>
using Event = sdlgame::event::Event;
std::vector<Event> sdlgame::event::current_events;
Event sdlgame::event::tmp;
sdlgame::event::Event::Event() = default;
sdlgame::event::Event::Event(SDL_Event e)
{
    tmp_e = e;
    type = e.type;
    /**
     * @todo: leave these here in case need, now type only is good enough
     */
    if (e.type == SDL_WINDOWEVENT)
    {
        timestamp = e.window.timestamp;
        dict["windowID"] = e.window.windowID; /**< The associated window */
        dict["event"] = e.window.event;
    }
    else if (e.type == SDL_KEYDOWN or e.type == SDL_KEYUP)
    {
        timestamp = e.key.timestamp;
        dict["key"] = e.key.keysym.scancode;
    }
    else if (e.type == SDL_QUIT)
    {
        // lol, just here to write const event
    }
    else if (e.type == SDL_MOUSEWHEEL)
    {
        timestamp = e.wheel.timestamp;
        dict["x"] = e.wheel.x;
        dict["y"] = e.wheel.y;
    }
    else if (e.type == SDL_MOUSEBUTTONUP or e.type == SDL_MOUSEBUTTONDOWN)
    {
        timestamp = e.button.timestamp;
        dict["button"] = e.button.button;
        dict["x"] = e.button.x;
        dict["y"] = e.button.y;
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        timestamp = e.motion.timestamp;
        dict["x"] = e.motion.x;
        dict["y"] = e.motion.y;
        dict["xrel"] = e.motion.xrel;
        dict["yrel"] = e.motion.yrel;
    }
}
int64_t sdlgame::event::Event::operator[](std::string key)
{
    if (dict.find(key) != dict.end())
    {
        return dict[key];
    }
    else
    {
        throw std::invalid_argument("There's no such key: " + key);
    }
}
std::vector<Event> &sdlgame::event::get()
{
    current_events.clear();
    SDL_Event e;
    // while (SDL_PollEvent(&e))
    for(int i=1;i<=30;i++)
    {
        if(!SDL_PollEvent(&e)) break;
        current_events.push_back(Event(e));
    }
    return current_events;
}
Event tmp;
/**please only use this for user event*/
void sdlgame::event::post(Uint32 event_type)
{
    tmp.tmp_e.type = event_type;
    SDL_PushEvent(&tmp.tmp_e);
}