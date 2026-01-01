#pragma once
#ifndef SDLGAME_EVENT_
#define SDLGAME_EVENT_
#include "SDL2/SDL_events.h"
#include <string>
#include <vector>
#include <map>
namespace sdlgame{
    namespace event
    {
        /**
         *  class represent a event like keyboard input or mouse click (anything happening in the game)
         */
        class Event
        {
        private:
            std::map<std::string, int64_t> dict;

        public:
            Uint32 type;
            Uint32 timestamp;
            SDL_Event tmp_e;
            Event();
            Event(SDL_Event e);
            int64_t operator[](std::string key);
        };
        extern std::vector<Event> current_events;
        extern Event tmp;
        std::vector<Event> &get();
        /**please only use this for user event*/
        void post(Uint32 event_type);
    }
}

#endif