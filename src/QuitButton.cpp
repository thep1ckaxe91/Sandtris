#include "QuitButton.hpp"
#include "engine.hpp"
#include "Game.hpp"
QuitButton::QuitButton(Game &game) : Button()
{
    game = &game;
    set_images(game->m_images.quit_button_idle,game->m_images.quit_button_hover,game->m_images.quit_button_click);
    rect = (*image).get_rect();
}
QuitButton::QuitButton(){}
void QuitButton::handle_event(const Event &event)
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