#include "mixer.hpp"
#include "stdio.h"
#include <SDL2/SDL_mixer.h>
#include <utility>

namespace sdlgame::mixer {
void set_num_channels(int count) { Mix_AllocateChannels(count); }
void init(int freq, uint16_t size, int channels, int buffer) {
  size = (size == 16 ? AUDIO_S16SYS : AUDIO_F32SYS);
  if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3) {
    printf("Failed to init mp3 type\nErr:%s\n", Mix_GetError());
  }
  if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG) {
    printf("Failed to init ogg type\nErr:%s\n", Mix_GetError());
  }
  if ((Mix_Init(MIX_INIT_WAVPACK) & MIX_INIT_WAVPACK) != MIX_INIT_WAVPACK) {
    printf("Failed to init wav pack\nErr:%s\n", Mix_GetError());
  }
  if (Mix_OpenAudio(freq, size, channels, buffer)) {
    printf("Failed to init mixer\nErr:%s\n", Mix_GetError());
    exit(0);
  } else {
    printf("Mixer successfully initialized\n");
  }
}
int get_num_channels() { return Mix_AllocateChannels(-1); }

int convert_volume_value(float value) {
  return int((value >= 1 ? 1 : value) / 1.0 * 128);
}

Channel::Channel(int id) : id(id), volume(1.0f) {}

void Channel::play(Sound sound, int loops, int maxtime_ms, int fade_ms) {
  if (Mix_FadeInChannelTimed(id, sound.chunk.get(), loops, fade_ms,
                             maxtime_ms) == -1) [[unlikely]] {
    printf("No channel available\nErr:%s\n", Mix_GetError());
    exit(0);
  }
}
void Channel::set_volume(float value) {
  Mix_Volume(id, convert_volume_value(value));
}
int Channel::get_volume() { return Mix_Volume(id, -1); }

Sound::Sound() : channel(-1), volume(1.0f) {}
Sound::Sound(fs::path path) : channel(-1), volume(1.0f) {
  auto new_chunk = Mix_LoadWAV(path.string().c_str());
  if (!new_chunk) [[unlikely]] {
    printf("Cant load track\nErr:%s\n", Mix_GetError());
    exit(0);
  }
  chunk.reset(new_chunk, memory::SDLDeleter{});
}
Sound::Sound(Sound &&oth) noexcept
    : channel(oth.channel), volume(oth.volume), chunk(std::move(oth.chunk)) {}

Sound &Sound::operator=(const Sound &oth) {
  chunk = oth.chunk;
  volume = oth.volume;
  channel = oth.channel;
  return *this;
}

Sound &Sound::operator=(Sound &&oth) noexcept {
  chunk = std::move(oth.chunk);
  volume = oth.volume;
  channel = oth.channel;
  return *this;
}

Channel Sound::play(int loops, int maxtime_ms, int fade_ms) {
  channel = Mix_FadeInChannelTimed(-1, chunk.get(), loops, fade_ms, maxtime_ms);
  if (channel == -1) [[unlikely]] {
    printf("No channel available\nErr:%s\n", Mix_GetError());
  }
  return Channel(channel);
}
void Sound::load(const fs::path &path) {
  auto new_chunk = Mix_LoadWAV(path.string().c_str());
  if (!new_chunk) [[unlikely]] {
    printf("Cant load track\nErr:%s\n", Mix_GetError());
    exit(0);
  }
  chunk.reset(new_chunk, memory::SDLDeleter{});
}
void Sound::fadeout(int ms) { Mix_FadeOutChannel(channel, ms); }
void Sound::set_volume(float value) {
  Mix_VolumeChunk(chunk.get(), convert_volume_value(value));
}
int Sound::get_volume() const { return Mix_VolumeChunk(chunk.get(), -1); }
} // namespace sdlgame::mixer
