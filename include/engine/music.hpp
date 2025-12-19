// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include <string>
#include <memory>
#include "SDL3_mixer/SDL_mixer.h"

namespace sdlgame {
    namespace music
    {
        extern std::shared_ptr<MIX_Audio> music_audio;
        extern MIX_Track *music_track;
        
        void load(std::string path);
        void play(int loop = 0, int fadein_ms = 0);
        void pause();
        void resume();
        void stop();
        bool is_playing();
        double duration();
        void set_volume(float value);
        float get_volume();
    }
}