#pragma once
#ifndef CREDIT_HPP
#define CREDIT_HPP

#include "BackButton.hpp"
#include "Game.hpp"
#include "Scene.hpp"
#include <memory>

class Credit : public Scene {
public:
  std::shared_ptr<BackButton> back_button;
  const Vector2 bb_pos = Vector2(123, 123);
  Credit(Game &game);
  void handle_event(const Event &event) override;
  void update() override;
  void draw() override;
};

#endif
