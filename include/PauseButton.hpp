// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#include "Button.hpp"
#include "Game.hpp"

class PauseButton : public Button
{
public:
    Game *game;
    PauseButton(Game &game);
    PauseButton();
    void on_click();
    void update();
    void handle_event(Event &event);
};

