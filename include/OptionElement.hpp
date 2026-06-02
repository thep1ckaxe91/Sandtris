#pragma once
#ifndef OPTION_ELEMENT_HPP
#define OPTION_ELEMENT_HPP
#include "Game.hpp"
#include "Slider.hpp"

class SFXVolumeSlider : public Slider {
public:
  Game &game;
  SFXVolumeSlider(Game &game, Vector2 topleft, float value, float length,
                  float max_value);
  void update();
  void handle_event(const Event &event);
  void draw();
  void on_change_value();
};

class MusicVolumeSlider : public Slider {
public:
  Game &game;
  MusicVolumeSlider(Game &game, Vector2 topleft, float value, float length,
                    float max_value);
  void update();
  void handle_event(const Event &event);
  void draw();
  void on_change_value();
};

class FullscreenSlider : public Slider {
public:
  Game &game;
  FullscreenSlider(Game &game, Vector2 topleft, float value, float length,
                   float max_value);
  void update();
  void handle_event(const Event &event);
  void draw();
  void on_change_value();
};

#endif