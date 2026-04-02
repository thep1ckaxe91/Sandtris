#pragma once
#ifndef SDLGAME_MUSIC_
#define SDLGAME_MUSIC_
#include <filesystem>
#include "memory.hpp"
#include "SDL2/SDL_mixer.h"

namespace fs = std::filesystem;

namespace sdlgame {
    namespace music
    {
        extern memory::SDLUniquePtr<Mix_Music> music;
        void load(const fs::path& path);
        void play(int loop = 0, int fadein_ms=0);
        void pause();
        void resume();
        void stop();
        bool is_playing();
        double duration();
        void set_volume(float value);
        void get_volume();
        int convert_volume_value(float value);
    }
}

#endif