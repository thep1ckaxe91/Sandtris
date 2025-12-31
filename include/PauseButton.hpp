#ifndef PAUSE_BUTTON_HPP
#define PAUSE_BUTTON_HPP

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

#endif