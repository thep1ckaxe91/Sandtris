#include "music.hpp"
#include "SDL2/SDL_mixer.h"
#include "memory.hpp"

namespace sdlgame::music {
memory::SDLUniquePtr<Mix_Music> music;

void load(fs::path path) {

  auto new_music = Mix_LoadMUS(path.c_str());
  if (!new_music) {
    printf("Cant load music\nErr:%s\n", Mix_GetError());
    exit(1);
  }
  music.reset(new_music);
}
void play(int loop, int fadein_ms) {

  if (Mix_FadeInMusic(music.get(), loop, fadein_ms)) {
    printf("Cant play music\nErr:%s\n", Mix_GetError());
    // exit(1);
  }
}
void pause() { Mix_PauseMusic(); }
void resume() { Mix_ResumeMusic(); }
void stop() { Mix_HaltMusic(); }
bool is_playing() { return Mix_PlayingMusic(); }
// Return duration of the music in second
double duration() { return Mix_MusicDuration(music.get()); }
int convert_volume_value(float value) {
  return int((value >= 1 ? 1 : value) / 1.0 * 128);
}
void set_volume(float value) { Mix_VolumeMusic(convert_volume_value(value)); }
void get_volume() { Mix_VolumeMusic(-1); }
} // namespace sdlgame::music