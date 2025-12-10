#include "BackButton.hpp"
#include "Game.hpp"
#include "scene_transitions.hpp"

BackButton::BackButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.back_button_idle,this->game->images.back_button_hover,this->game->images.back_button_click);
    this->rect = this->image.getRect();
}
BackButton::BackButton(){}
void BackButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void BackButton::on_click()
{
    OutFade *out = new OutFade(0.5);
    InFade *in = new InFade(0.5);
    this->game->remove_scene(out,in);
}
void BackButton::update()
{
    Button::update();
}