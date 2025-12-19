// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "Game.hpp"
#include "Button.hpp"
class StartButton : public Button
{
public:
    Game* game;
    StartButton(Game &game);
    StartButton();
    void on_click();
    void handle_event(Event &event);
    void update();
};
