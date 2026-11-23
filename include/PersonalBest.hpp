#pragma once
#include <sdlgame/math.hpp>
#include <sdlgame/surface.hpp>
#ifndef PERSONAL_BEST_HPP
#define PERSONAL_BEST_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include <memory>
#include <sdlgame/font.hpp>

using sdlgame::math::Vector2;

class PersonalBest : public Scene {
  constexpr static Vector2 pb_center = Vector2(81, 79);
  constexpr static Vector2 bb_pos = Vector2(66, 103);

  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> pb_surf;
  sdlgame::font::Font pb_font;
  sdlgame::rect::Rect pb_rect;
  std::shared_ptr<BackButton> back_button;
  int score;
public:
  PersonalBest(Game &game);
  void update() override;
  void draw() override;
  void handle_event(const sdlgame::event::Event &event) override;
};

#endif
