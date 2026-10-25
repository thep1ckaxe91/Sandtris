#pragma once
#ifndef SFX_HPP
#define SFX_HPP

// Load all sfx for use here
#include <filesystem>
#include <sdlgame/mixer.hpp>

namespace fs = std::filesystem;
const fs::path sfx_path{fs::path{"assets"} / "audio" / "sfx"};

class SFX {
public:
  sdlgame::mixer::Sound button_click;
  sdlgame::mixer::Sound button_hover;
  sdlgame::mixer::Sound count_down;
  sdlgame::mixer::Sound count_down_start;
  sdlgame::mixer::Sound game_over;
  sdlgame::mixer::Sound merge;
  sdlgame::mixer::Sound rotate;
  sdlgame::mixer::Sound scoring;
  sdlgame::mixer::Sound transition_in;
  sdlgame::mixer::Sound transition_out;
  sdlgame::mixer::Sound soft_wind_blow;
  SFX();
  void load();
};

#endif