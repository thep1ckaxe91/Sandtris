#pragma once

#include "Button.hpp"
#include "Game.hpp"
class ResumeButton : public Button 
{
public:
    Game *game;
    ResumeButton(Game &game);
    ResumeButton();
    void update(); 
    void handle_event(Event &event);
    void on_click();
};

