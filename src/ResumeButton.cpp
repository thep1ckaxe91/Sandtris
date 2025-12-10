#include "ResumeButton.hpp"
#include "SaveData.hpp"
#include "Grid.hpp"
#include "GamePlay.hpp"
#include "scene_transitions.hpp"
ResumeButton::ResumeButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.resume_button_idle,this->game->images.resume_button_hover,this->game->images.resume_button_click);
}
ResumeButton::ResumeButton() = default;
void ResumeButton::update()
{
    Button::update();
}
void ResumeButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void ResumeButton::on_click()
{
    InSwipeDown *in = new InSwipeDown(1);
    OutSwipeDown *out = new OutSwipeDown(1);
    GamePlay *next = new GamePlay(*game);
    next->load_grid(load_grid_data(game));
    this->game->pop_scene(out,next,in);
}