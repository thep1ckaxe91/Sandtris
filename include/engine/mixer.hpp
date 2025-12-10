#pragma once
#ifndef SDLGAME_MIXER_
#define SDLGAME_MIXER_
#include "SDL2/SDL_mixer.h"
#include <string>
#include <map>
namespace sdlgame 
{
    /**
     * @brief due to its complexity, it's best practice to call init function as use in main function
     */
    namespace mixer
    {
        extern std::map<Mix_Chunk*,int> __chunk_pool;
        /*set number of playback channel, default is 8*/
        void set_num_channels(int count);
        /**
         * @param freq freqency of the audio
         * @param size determine the audio format, you can choose between 16 or 32 bit audio
         * @param channels 1 for mono, 2 for stereo
         * @param buffer size of sample that fed to the computer, the larger then better qualiy, but more audio lag
         * @param devicename name of the device, leave it as empty to be default system
         * Init the mixer module, it not guarantee that all flag can be sucessfully init since it depend on what in the os
         */
        void init(int freq = 44100, Uint16 size = 16, int channels = 2, int buffer = 512);
        int get_num_channels();
        class Sound;

        int convert_volume_value(float value);
        /**
         * A Channel object to controll playback at certain channel id,
         * in its core, it just a int var hold the id to the channel after all
         */
        class Channel
        {
        private:
            int id;
            float volume;

        public:
            Channel(int id);
            void play(Sound sound, int loops = 0, int maxtime_ms = -1, int fade_ms = 0);
            void set_volume(float value);
            int get_volume();
        };

        /**
         * class represent a Sound object, should be only support WAV and OGG,
         * if you need to play music, use music namepsace instead
         */
        class Sound
        {
        private:
            int channel;
            float volume;
        public:
            Mix_Chunk *chunk;
            Sound();
            Sound(std::string path);
            Sound &operator=(const Sound& oth);
            /**
             * @param loops -1 to loop infinitely, 0 is play once, 1 is twice...
             * @param maxtime_ms maximum time in miliseconds the sound will be play in ms until it stop
             * @param fade_ms fade in time in miliseconds
             */
            Channel play(int loops = 0, int maxtime_ms = -1, int fade_ms = 0);
            void load(std::string path);
            void fadeout(int ms);
            /**
             * This will set the playback volume (loudness) for this Sound.
             * This will immediately affect the Sound if it is playing.
             * It will also affect any future playback of this Sound.
             * @param value (float) --
                volume in the range of 0.0 to 1.0 (inclusive)
                If value < 0.0, the volume will not be changed
                If value > 1.0, the volume will be set to 1.0
            */
            void set_volume(float value);
            int get_volume() const;
            ~Sound();
        };

    }
}

#endif