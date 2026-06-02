#include "OptionButton.hpp"
#include "Option.hpp"
#include "scene_transitions.hpp"
#include <memory>

OptionButton::OptionButton(Game &g) : game(&g) {
  set_images(game->images.option_button_idle,
             game->images.option_button_hover,
             game->images.option_button_click);
}

void OptionButton::update() { Button::update(); }
void OptionButton::handle_event(const Event &event) {
  Button::handle_event(event);
}
void OptionButton::on_click() {
  auto in = std::make_unique<InFade>(1);
  auto out = std::make_unique<OutFade>(1);
  auto next = std::make_unique<Option>(*game);
  game->add_scene(std::move(out), std::move(next), std::move(in));
}
