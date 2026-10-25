#pragma once
#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include "SFX.hpp"
#include <sdlgame/event.hpp>

class AudioManager {
private:
  float sfx_volume;
  float music_volume;

public:
  SFX sfx;
  AudioManager();
  void update();
  void handle_event(const sdlgame::event::Event &event);
  void set_sfx_volume(float value);
  float get_sfx_volume();
  void set_music_volume(float value);
  float get_music_volume();
};

#endif