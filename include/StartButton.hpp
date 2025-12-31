#ifndef STARTBUTTON_HPP
#define STARTBUTTON_HPP
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

#endif