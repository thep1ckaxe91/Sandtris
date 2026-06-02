#pragma once
#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "MenuButton.hpp"
#include "RetryButton.hpp"
#include "Scene.hpp"
#include "engine.hpp"
#include <memory>

class GameOver : public Scene {
  std::shared_ptr<MenuButton> menu;
  std::shared_ptr<RetryButton> retry;
  Font score_font;
  Surface new_score_surf;
  Rect new_score_rect;
  Surface pb_surf;
  Rect pb_rect;
  int new_score;
  int pb;

public:
  GameOver(Game &game, int new_score);
  void handle_event(const Event &event) override;
  void update() override;
  void draw() override;
};
#endif
