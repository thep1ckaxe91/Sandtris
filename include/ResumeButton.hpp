#pragma once
#ifndef RESUME_BUTTON_HPP
#define RESUME_BUTTON_HPP

#include "Button.hpp"
#include "Game.hpp"

class ResumeButton : public Button {
public:
  Game *game; // FIXME: why pointer instead of const lref?
  ResumeButton(Game &game);
  void update();
  void handle_event(const sdlgame::event::Event &event);
  void on_click();
};

#endif