#include "PauseButton.hpp"
#include "Pause.hpp"
#include "scene_transitions.hpp"
PauseButton::PauseButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.pause_button_idle,this->game->images.pause_button_hover,this->game->images.pause_button_click);
    this->rect = this->image.getRect();
}
PauseButton::PauseButton()=default;
void PauseButton::update()
{
    Button::update();
}
void PauseButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void PauseButton::on_click()
{
    OutFade *out = new OutFade(1);
    InFade *in = new InFade(1);
    Pause *next = new Pause(*game);
    this->game->add_scene(out,next,in);
}