#pragma once
#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"
class MenuButton : public Button {
public:
  Game* game;
  MenuButton(Game &game);

  void on_click();
  void handle_event(const Event &event);
  void update();
};
#endif