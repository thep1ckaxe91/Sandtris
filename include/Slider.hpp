#pragma once
#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <sdlgame/color.hpp>
#include <sdlgame/event.hpp>
#include <sdlgame/font.hpp>
#include <sdlgame/math.hpp>
#include <sdlgame/rect.hpp>
#include <sdlgame/surface.hpp>

/**
 * @brief Slider is expect to inherit.
 * Call set color and overwrite draw and on_change_value should be good enough
 *
 *
 */
class Slider {
protected:
  sdlgame::rect::Rect nob;
  sdlgame::math::Vector2 topleft;
  sdlgame::font::Font label_font;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> label_surf;
  sdlgame::rect::Rect label_rect;
  sdlgame::color::Color nob_color;
  sdlgame::color::Color value_color;
  sdlgame::color::Color no_value_color;
  float value;
  float slide_length;
  float max_value;
  bool holding;

public:
  Slider(sdlgame::math::Vector2 topleft, float value = 1, float slide_length = 48,
         float max_value = 1);
  Slider();
  void set_label(std::string text, sdlgame::color::Color color);
  void set_color(sdlgame::color::Color nobColor, sdlgame::color::Color valid,
                 sdlgame::color::Color invalid);
  virtual void update();
  virtual void handle_event(const sdlgame::event::Event &event);
  virtual void draw() = 0;
  virtual void on_change_value() = 0;
};

#endif