#ifndef RESUME_BUTTON_HPP
#define RESUME_BUTTON_HPP

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

#endif