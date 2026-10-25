#pragma once
#ifndef STARTBUTTON_HPP
#define STARTBUTTON_HPP

#include <sdlgame/event.hpp>
#include "Button.hpp"
#include "Game.hpp"
class StartButton : public Button {
public:
  Game* game;
  StartButton(Game &game);
  void on_click();
  void handle_event(const sdlgame::event::Event &event);
  void update();
};

#endif