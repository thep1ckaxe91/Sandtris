#ifndef BACKBUTTON_HPP
#define BACKBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"
class BackButton : public Button
{
public:
    Game *game;
    BackButton(Game &game);
    BackButton();
    void on_click();
    void handle_event(Event &event);
    void update();
};

#endif