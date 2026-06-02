#pragma once
#ifndef HOW_TO_PLAY_HPP
#define HOW_TO_PLAY_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include <memory>

class HowToPlay : public Scene {
public:
  std::shared_ptr<BackButton> back_button;
  double height_pos;
  const Vector2 bb_pos = Vector2(123, 123);
  HowToPlay(Game &game);
  void handle_event(const Event &event) override;
  void update() override;
  void draw() override;
};

#endif
