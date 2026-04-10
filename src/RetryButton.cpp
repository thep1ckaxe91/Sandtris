#include "RetryButton.hpp"
#include "GamePlay.hpp"
#include "SaveData.hpp"
#include "scene_transitions.hpp"
#include <memory>
RetryButton::RetryButton(Game &game) {
  game = &game;
  set_images(game->images.retry_button_idle,
                   game->images.retry_button_hover,
                   game->images.retry_button_click);
  rect = (*image).get_rect();
}
RetryButton::RetryButton() = default;
void RetryButton::handle_event(Event &event) { Button::handle_event(event); }
void RetryButton::on_click() {
  auto out = std::make_unique<OutSwipeDown>();
  auto in = std::make_unique<InSwipeDown>();
  auto next = std::make_unique<GamePlay>(*game);
  delete_grid_data();
  game->clear_scene(std::move(out), std::move(next), std::move(in));
}
void RetryButton::update() { Button::update(); }
