#pragma once
#ifndef SDLGAME_MUSIC_
#define SDLGAME_MUSIC_
#include <string>
#include "SDL2/SDL_mixer.h"
namespace sdlgame {
    namespace music
    {
        extern Mix_Music *music;
        void load(std::string path);
        void play(int loop = 0, int fadein_ms=0);
        void pause();
        void resume();
        void stop();
        bool is_playing();
        // Return duration of the music in second
        double duration();
        void set_volume(float value);
        void get_volume();
        int convert_volume_value(float value);
    }
}

#endif