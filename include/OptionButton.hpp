#pragma once

#include "Button.hpp"
#include "Game.hpp"
class OptionButton : public Button
{
public:
    Game *game;
    OptionButton(Game &game);
    OptionButton();
    void update();
    void handle_event(Event &event);
    void on_click();
};

