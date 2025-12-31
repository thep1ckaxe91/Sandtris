#include "QuitButton.hpp"
#include "engine/engine.hpp"
#include "Game.hpp"
QuitButton::QuitButton(Game &game) : Button()
{
    this->game = &game;
    this->set_images(this->game->images.quit_button_idle,this->game->images.quit_button_hover,this->game->images.quit_button_click);
    this->rect = this->image.getRect();
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