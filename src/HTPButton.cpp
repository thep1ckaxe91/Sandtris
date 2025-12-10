#include "HTPButton.hpp"
#include "HowToPlay.hpp"
#include "scene_transitions.hpp"
HTPButton::HTPButton(Game &game)
{
    this->game = &game;
    set_images(this->game->images.htp_button_idle, this->game->images.htp_button_hover,this->game->images.htp_button_click);
    this->rect = this->image.getRect();
}
HTPButton::HTPButton() = default;
void HTPButton::update()
{
    Button::update();
}
void HTPButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void HTPButton::on_click()
{
    InFade *in = new InFade(1);
    OutFade *out = new OutFade(1);
    HowToPlay *next = new HowToPlay(*this->game);
    this->game->add_scene(out,next,in);
}