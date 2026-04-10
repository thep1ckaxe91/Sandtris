#include "BackButton.hpp"
#include "Game.hpp"
#include "scene_transitions.hpp"
#include <memory>

BackButton::BackButton(Game &game) {
  game = &game;
  set_images(game->images.back_button_idle,
                   game->images.back_button_hover,
                   game->images.back_button_click);
  rect = (*image).get_rect();
}
BackButton::BackButton() {}
void BackButton::handle_event(Event &event) { Button::handle_event(event); }
void BackButton::on_click() {
  auto out = std::make_unique<OutFade>(0.5);
  auto in = std::make_unique<InFade>(0.5);
  game->remove_scene(std::move(out), std::move(in));
}
void BackButton::update() { Button::update(); }