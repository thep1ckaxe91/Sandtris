#include "StartButton.hpp"
#include "GamePlay.hpp"
#include "engine.hpp"
#include "scene_transitions.hpp"

StartButton::StartButton(Game &g) : game(&g) {
  set_images(game->images.start_button_idle,
             game->images.start_button_hover,
             game->images.start_button_click);
}

void StartButton::handle_event(const Event &event) {
  Button::handle_event(event);
}
void StartButton::on_click() {
  auto out = std::make_unique<OutSwipeDown>();
  auto in = std::make_unique<InSwipeDown>();
  auto next = std::make_unique<GamePlay>(*game);
  game->pop_scene(std::move(out), std::move(next), std::move(in));
}
void StartButton::update() { Button::update(); }
