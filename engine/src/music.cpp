#include "music.hpp"
#include "SDL2/SDL_mixer.h"
#include "memory.hpp"
#include <SDL2/SDL_mixer.h>
#include <iostream>

namespace sdlgame::music {
static memory::SDLUniquePtr<Mix_Music> music;

void load(fs::path path) {

  auto new_music = Mix_LoadMUS(path.string().c_str());

  if (!new_music) {
    printf("Cant load music\nErr:%s\n", Mix_GetError());
    exit(1);
  }

  music.reset(new_music);
}
void play(int loop, int fadein_ms) {

  if (!music)
    return;

  if (Mix_FadeInMusic(music.get(), loop, fadein_ms)) {
    std::cerr << "Cant play music\nErr:" << Mix_GetError() << '\n';
  }
}
void pause() { Mix_PauseMusic(); }
void resume() { Mix_ResumeMusic(); }
void stop() { Mix_HaltMusic(); }
bool is_playing() { return Mix_PlayingMusic() != 0; }
// Return duration of the music in second
double duration() { return Mix_MusicDuration(music.get()); }
int convert_volume_value(float value) {
  return static_cast<int>(std::clamp(value, 0.0f, 1.0f) * MIX_MAX_VOLUME);
}

void set_volume(float value) { Mix_VolumeMusic(convert_volume_value(value)); }

float get_volume() {
  return static_cast<float>(Mix_VolumeMusic(-1)) / MIX_MAX_VOLUME;
}
} // namespace sdlgame::music