#pragma once
#include <surface.hpp>
#ifndef PERSONAL_BEST_HPP
#define PERSONAL_BEST_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include <memory>
#include <sdlgame/font.hpp>

class PersonalBest : public Scene {
public:
  sdlgame::font::Font pb_font;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> pb_surf;
  sdlgame::rect::Rect pb_rect;
  const sdlgame::math::Vector2 pb_center = sdlgame::math::Vector2(81, 79);
  int score;
  std::shared_ptr<BackButton> back_button;
  const sdlgame::math::Vector2 bb_pos = sdlgame::math::Vector2(66, 103);
  PersonalBest(Game &game);
  void update() override;
  void draw() override;
  void handle_event(const sdlgame::event::Event &event) override;
};

#endif
