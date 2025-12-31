#include "MenuButton.hpp"
#include "scene_transitions.hpp"
#include "MainMenu.hpp"
MenuButton::MenuButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.menu_button_idle,this->game->images.menu_button_hover, this->game->images.menu_button_click);
    this->rect = this->image.getRect();
}
MenuButton::MenuButton()=default;
void MenuButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void MenuButton::on_click()
{
    OutSwipeDown *out = new OutSwipeDown();
    InSwipeDown *in = new InSwipeDown();
    MainMenu *next = new MainMenu(*game);
    this->game->clear_scene(out,next,in);
}
void MenuButton::update()
{
    Button::update();
}
