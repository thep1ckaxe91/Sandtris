#include "StartButton.hpp"
#include "GamePlay.hpp"
#include "scene_transitions.hpp"
#include "engine/engine.hpp"
StartButton::StartButton(Game &game) : Button()
{
    this->game = &game;
    this->set_images(this->game->images.start_button_idle,this->game->images.start_button_hover,this->game->images.start_button_click);
    this->rect = this->image.getRect();
}
StartButton::StartButton() = default;
void StartButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void StartButton::on_click()
{
    OutSwipeDown *out = new OutSwipeDown();
    InSwipeDown *in = new InSwipeDown();
    GamePlay *next = new GamePlay(*this->game);
    this->game->pop_scene(out,next,in);
}
void StartButton::update()
{
    Button::update();
}
