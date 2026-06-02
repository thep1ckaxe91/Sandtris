#pragma once
#ifndef RESUME_BUTTON_HPP
#define RESUME_BUTTON_HPP

#include "Button.hpp"
#include "Game.hpp"
class ResumeButton : public Button {
public:
  Game* game;
  ResumeButton(Game &game);
  void update();
  void handle_event(const Event &event);
  void on_click();
};

#endif