#pragma once
#ifndef QUITBUTTON_HPP
#define QUITBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"
class QuitButton : public Button {
public:
  Game* game;
  QuitButton(Game &game);

  void on_click();
  void handle_event(const Event &event);
  void update();
};

#endif