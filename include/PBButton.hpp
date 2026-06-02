#pragma once
#ifndef PBBUTTON_HPP
#define PBBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"

class PBButton : public Button {
public:
  Game* game;
  PBButton(Game &game);
  void on_click();
  void update();
  void handle_event(const Event &event);
};

#endif