#include "PBButton.hpp"
#include "PersonalBest.hpp"
#include "scene_transitions.hpp"
PBButton::PBButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.pb_button_idle,this->game->images.pb_button_hover,this->game->images.pb_button_click);
    this->rect = this->image.getRect();
}
PBButton::PBButton() = default;
void PBButton::on_click()
{
    InFade *in = new InFade(1);
    OutFade *out = new OutFade(1);
    PersonalBest *next = new PersonalBest(*game);

    this->game->add_scene(out,next,in);
}

void PBButton::update()
{
    Button::update();
}

void PBButton::handle_event(Event &event)
{
    Button::handle_event(event);
}