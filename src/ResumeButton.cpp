#include "ResumeButton.hpp"
#include "GamePlay.hpp"
#include "SaveData.hpp"
#include "scene_transitions.hpp"
ResumeButton::ResumeButton(Game &game) {
  game = &game;
  set_images(game->images.resume_button_idle,
                   game->images.resume_button_hover,
                   game->images.resume_button_click);
}
ResumeButton::ResumeButton() = default;
void ResumeButton::update() { Button::update(); }
void ResumeButton::handle_event(Event &event) { Button::handle_event(event); }
void ResumeButton::on_click() {
  auto out = std::make_unique<OutSwipeDown>(1);
  auto in = std::make_unique<InSwipeDown>(1);
  auto next = std::make_unique<GamePlay>(*game);
  next->load_grid(load_grid_data(std::move(game)));
  game->pop_scene(std::move(out), std::move(next), std::move(in));
}