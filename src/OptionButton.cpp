#include "OptionButton.hpp"
#include "Option.hpp"
#include "scene_transitions.hpp"
OptionButton::OptionButton(Game &game)
{
    this->game = &game;
    set_images(this->game->images.option_button_idle, this->game->images.option_button_hover,this->game->images.option_button_click);
    this->rect = this->image.getRect();
}
OptionButton::OptionButton() = default;
void OptionButton::update()
{
    Button::update();
}
void OptionButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void OptionButton::on_click()
{
    InFade *in = new InFade(1);
    OutFade *out = new OutFade(1);
    Option *next = new Option(*this->game);
    this->game->add_scene(out,next,in);
}