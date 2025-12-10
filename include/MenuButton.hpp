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
