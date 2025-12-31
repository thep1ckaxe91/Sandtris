#ifndef HTP_BUTTON_HPP
#define HTP_BUTTON_HPP

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

#endif