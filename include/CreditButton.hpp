#ifndef CREDIT_BUTTON_HPP
#define CREDIT_BUTTON_HPP

#include "Button.hpp"
#include "Game.hpp"
class CreditButton : public Button
{
public:
    Game *game;
    CreditButton(Game &game);
    CreditButton();
    void update();
    void handle_event(Event &event);
    void on_click();
};

#endif