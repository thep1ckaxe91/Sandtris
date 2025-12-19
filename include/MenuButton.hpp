// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "Button.hpp"
#include "Game.hpp"
class MenuButton : public Button
{
    Game *game;
public:
    MenuButton(Game &game);
    MenuButton();
    void on_click();
    void handle_event(Event &event);
    void update();
};
