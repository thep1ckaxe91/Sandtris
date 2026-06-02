#pragma once
#ifndef OPTION_HPP
#define OPTION_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "OptionElement.hpp"
#include "Scene.hpp"
#include <memory>

class Option : public Scene {
public:
  std::shared_ptr<BackButton> back_button;
  std::shared_ptr<SFXVolumeSlider> sfx_slider;
  std::shared_ptr<MusicVolumeSlider> music_slider;
  std::shared_ptr<FullscreenSlider> fs_slider;
  Option(Game &game);
  void update() override;
  void handle_event(const Event &event) override;
  void draw() override;
};
#endif
