// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "SDL3/SDL_events.h"
#include <string>
#include <vector>
#include <unordered_map>
namespace sdlgame{
    namespace event
    {
        /**
         *  class represent a event like keyboard input or mouse click (anything happening in the game)
         */
        class Event
        {
        private:
            std::unordered_map<std::string, int64_t> dict;

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
