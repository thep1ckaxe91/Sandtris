#include "CreditButton.hpp"
#include "Credit.hpp"
#include "scene_transitions.hpp"
CreditButton::CreditButton(Game &game)
{
    this->game = &game;
    set_images(this->game->images.credit_button_idle, this->game->images.credit_button_hover,this->game->images.credit_button_click);
    this->rect = this->image.getRect();
}
CreditButton::CreditButton() = default;
void CreditButton::update()
{
    Button::update();
}
void CreditButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void CreditButton::on_click()
{
    InFade *in = new InFade(1);
    OutFade *out = new OutFade(1);
    Credit *next = new Credit(*this->game);
    this->game->add_scene(out,next,in);
}