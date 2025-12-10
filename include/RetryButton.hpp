#ifndef RETRYBUTTON_HPP
#define RETRYBUTTON_HPP
#include "Button.hpp"
#include "Game.hpp"
class RetryButton : public Button
{
    Game *game;
public:
    RetryButton(Game &game);
    RetryButton();
    void on_click();
    void handle_event(Event &event);
    void update();
};
#endif