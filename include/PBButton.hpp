#pragma once
#include "Button.hpp"
#include "Game.hpp"

class PBButton : public Button
{
public:
    Game *game;
    PBButton(Game &game);
    PBButton();
    void on_click();
    void update();
    void handle_event(Event &event);
};

