#pragma once
#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "engine.hpp"

/**
 * @brief Slider is expect to inherit.
 * Call set color and overwrite draw and on_change_value should be good enough
 *
 *
 */
class Slider {
protected:
  Rect nob;
  Vector2 topleft;
  Font label_font;
  Surface label_surf;
  Rect label_rect;
  Color nob_color;
  Color value_color;
  Color no_value_color;
  float value;
  float slide_length;
  float max_value;
  bool holding;

public:
  Slider(Vector2 topleft, float value = 1, float slide_length = 48,
         float max_value = 1);
  Slider();
  void set_label(std::string text, Color color);
  void set_color(Color nobColor, Color valid, Color invalid);
  virtual void update();
  virtual void handle_event(const Event &event);
  virtual void draw() = 0;
  virtual void on_change_value() = 0;
};

#endif