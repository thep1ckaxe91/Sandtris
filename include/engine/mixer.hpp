// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "SDL3_mixer/SDL_mixer.h"
#include <string>
#include <memory>

namespace sdlgame
{
    namespace mixer
    {
        extern MIX_Mixer *_mixer_device;

        void init(int freq = 44100, Uint16 size = 16, int channels = 2, int buffer = 512);
        void cleanup_finished_tracks();
        void quit();
        class Sound
        {
        private:
            float volume;
            mutable std::shared_ptr<MIX_Audio> audio_ptr;

        public:
            Sound();
            Sound(std::string path);

            Sound& operator=(const Sound& other);

            void play(int loops, int maxtime_ms, int fade_ms);
            void load(std::string path);

            void set_volume(float value);
            float get_volume() const;
        };
    }
}
