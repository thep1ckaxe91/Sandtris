#pragma once
#ifndef RETRYBUTTON_HPP
#define RETRYBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"
class RetryButton : public Button {
public:
  Game* game;
  RetryButton(Game &game);
  void on_click();
  void handle_event(const Event &event);
  void update();
};
#endif