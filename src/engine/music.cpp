#include"music.hpp"
#include <string>
#include "SDL2/SDL_mixer.h"
Mix_Music *sdlgame::music::music;
void sdlgame::music::load(std::string path)
{
    if (music != NULL)
        Mix_FreeMusic(music);
    music = Mix_LoadMUS(path.c_str());
    if (!music)
    {
        printf("Cant load music\nErr:%s\n", Mix_GetError());
        exit(0);
    }
}
void sdlgame::music::play(int loop, int fadein_ms)
{
    
    if(Mix_FadeInMusic(music, loop, fadein_ms))
    {
        printf("Cant play music\nErr:%s\n", Mix_GetError());
        exit(0);
    }
}
void sdlgame::music::pause()
{
    Mix_PauseMusic();
}
void sdlgame::music::resume()
{
    Mix_ResumeMusic();
}
void sdlgame::music::stop()
{
    Mix_HaltMusic();
}
bool sdlgame::music::is_playing()
{
    return Mix_PlayingMusic();
}
// Return duration of the music in second
double sdlgame::music::duration()
{
    return Mix_MusicDuration(music);
}
int sdlgame::music::convert_volume_value(float value)
{
    return int((value >= 1 ? 1 : value) / 1.0 * 128);
}
void sdlgame::music::set_volume(float value)
{
    Mix_VolumeMusic(convert_volume_value(value));

}
void sdlgame::music::get_volume()
{
    Mix_VolumeMusic(-1);

}