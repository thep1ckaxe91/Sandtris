#pragma once
#ifndef PERSONAL_BEST_HPP
#define PERSONAL_BEST_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include <memory>

class PersonalBest : public Scene {
public:
  Font pb_font;
  Surface pb_surf;
  Rect pb_rect;
  const Vector2 pb_center = Vector2(81, 79);
  int score;
  std::shared_ptr<BackButton> back_button;
  const Vector2 bb_pos = Vector2(66, 103);
  PersonalBest(Game &game);
  void update() override;
  void draw() override;
  void handle_event(const Event &event) override;
};

#endif
