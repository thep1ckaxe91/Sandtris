#include "mixer.hpp"
#include "stdio.h"
#include "string"
std::map<Mix_Chunk*,int> sdlgame::mixer::__chunk_pool;
void sdlgame::mixer::set_num_channels(int count)
{
    Mix_AllocateChannels(count);
}
/**
 * @param freq freqency of the audio
 * @param size determine the audio format, you can choose between 16 or 32 bit audio
 * @param channels 1 for mono, 2 for stereo
 * @param buffer size of sample that fed to the computer, the larger then better qualiy, but more audio lag
 * @param devicename name of the device, leave it as empty to be default system
 * Init the mixer module, it not guarantee that all flag can be sucessfully init since it depend on what in the os
 */
void sdlgame::mixer::init(int freq, Uint16 size, int channels, int buffer)
{
    size = (size == 16 ? AUDIO_S16SYS : AUDIO_F32SYS);
    if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        printf("Failed to init mp3 type\nErr:%s\n", Mix_GetError());
    }
    if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG)
    {
        printf("Failed to init ogg type\nErr:%s\n", Mix_GetError());
    }
    if ((Mix_Init(MIX_INIT_WAVPACK) & MIX_INIT_WAVPACK) != MIX_INIT_WAVPACK)
    {
        printf("Failed to init wav pack\nErr:%s\n", Mix_GetError());
    }
    if (Mix_OpenAudio(freq, size, channels, buffer))
    {
        printf("Failed to init mixer\nErr:%s\n", Mix_GetError());
        exit(0);
    }
    else
    {
        printf("Mixer successfully initialized\n");
    }
}
int sdlgame::mixer::get_num_channels()
{
    return Mix_AllocateChannels(-1);
}

int sdlgame::mixer::convert_volume_value(float value)
{
    return int((value >= 1 ? 1 : value) / 1.0 * 128);
}

sdlgame::mixer::Channel::Channel(int id)
{
    this->id = id;
    this->volume = 1;
}
void sdlgame::mixer::Channel::play(Sound sound, int loops, int maxtime_ms, int fade_ms){
    if(Mix_FadeInChannelTimed(this->id,sound.chunk,loops,fade_ms,maxtime_ms)==-1){
        printf("Cant play sound\nErr:%s\n",Mix_GetError());
        exit(0);
    }
}
void sdlgame::mixer::Channel::set_volume(float value){
    Mix_Volume(this->id,convert_volume_value(value));
}
int sdlgame::mixer::Channel::get_volume(){
    return Mix_Volume(this->id,-1);
}

sdlgame::mixer::Sound::Sound(){}
sdlgame::mixer::Sound::Sound(std::string path)
{
    chunk = Mix_LoadWAV(path.c_str());
    if (chunk == NULL)
    {
        printf("Cant load track\nErr:%s\n", Mix_GetError());
        exit(0);
    }
    __chunk_pool[this->chunk]=1;
}
sdlgame::mixer::Sound &sdlgame::mixer::Sound::operator=(const Sound& oth)
{
    this->chunk = oth.chunk;
    this->channel = oth.channel;
    this->volume = oth.volume;
    __chunk_pool[this->chunk]++;
    return *this;
}
/**
 * @param loops -1 to loop infinitely, 0 is play once, 1 is twice...
 * @param maxtime_ms maximum time in miliseconds the sound will be play in ms until it stop
 * @param fade_ms fade in time in miliseconds
 */
sdlgame::mixer::Channel sdlgame::mixer::Sound::play(int loops, int maxtime_ms, int fade_ms)
{
    this->channel = Mix_FadeInChannelTimed(-1, chunk, loops, fade_ms, maxtime_ms);
    if (this->channel == -1)
    {
        printf("cant play sound correctly\nErr:%s\n", Mix_GetError());
        // exit(0);
    }
    return Channel(this->channel);
}
void sdlgame::mixer::Sound::load(std::string path)
{
    if (chunk != NULL)
        Mix_FreeChunk(chunk);
    chunk = Mix_LoadWAV(path.c_str());
    if (chunk == NULL)
    {
        printf("Cant load track\nErr:%s\n", Mix_GetError());
        exit(0);
    }
}
void sdlgame::mixer::Sound::fadeout(int ms)
{
    Mix_FadeOutChannel(this->channel, ms);
}
void sdlgame::mixer::Sound::set_volume(float value)
{
    Mix_VolumeChunk(chunk, convert_volume_value(value));
}
int sdlgame::mixer::Sound::get_volume() const
{
    return Mix_VolumeChunk(chunk, -1);
}
sdlgame::mixer::Sound::~Sound()
{
    __chunk_pool[this->chunk]--;
    if(__chunk_pool.at(this->chunk)<=0)
    {
        if (chunk != NULL)
            Mix_FreeChunk(chunk);
    }
    this->chunk = 0;
}
