#include "RetryButton.hpp"
#include "scene_transitions.hpp"
#include "GamePlay.hpp"
#include "SaveData.hpp"
RetryButton::RetryButton(Game &game)
{
    this->game = &game;
    this->set_images(this->game->images.retry_button_idle,this->game->images.retry_button_hover, this->game->images.retry_button_click);
    this->rect = this->image.getRect();
}
RetryButton::RetryButton()=default;
void RetryButton::handle_event(Event &event)
{
    Button::handle_event(event);
}
void RetryButton::on_click()
{
    OutSwipeDown *out = new OutSwipeDown();
    InSwipeDown *in = new InSwipeDown();
    GamePlay *next = new GamePlay(*game);
    delete_grid_data();
    this->game->clear_scene(out,next,in);
}
void RetryButton::update()
{
    Button::update();
}
