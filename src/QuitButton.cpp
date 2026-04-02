#include "QuitButton.hpp"
#include "engine.hpp"
#include "Game.hpp"
QuitButton::QuitButton(Game &game) : Button()
{
    game = &game;
    set_images(game->images.quit_button_idle,game->images.quit_button_hover,game->images.quit_button_click);
    rect = (*image).getRect();
}
QuitButton::QuitButton(){}
void QuitButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void QuitButton::on_click()
{
    sdlgame::quit();
    exit(0);
}
void QuitButton::update()
{
    Button::update();
}