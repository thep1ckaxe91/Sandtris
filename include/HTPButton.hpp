#pragma once

#include "Button.hpp"
#include "Game.hpp"
class HTPButton : public Button
{
public:
    Game *game;
    HTPButton(Game &game);
    HTPButton();
    void update();
    void handle_event(Event &event);
    void on_click();
};

