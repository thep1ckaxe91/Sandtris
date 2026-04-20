#include "OptionButton.hpp"
#include "Option.hpp"
#include "scene_transitions.hpp"
#include <memory>
OptionButton::OptionButton(Game &game) {
  game = &game;
  set_images(game->m_images.option_button_idle,
             game->m_images.option_button_hover,
             game->m_images.option_button_click);
  rect = (*image).get_rect();
}
OptionButton::OptionButton() = default;
void OptionButton::update() { Button::update(); }
void OptionButton::handle_event(const Event &event) { Button::handle_event(event); }
void OptionButton::on_click() {
  auto in = std::make_unique<InFade>(1);
  auto out = std::make_unique<OutFade>(1);
  auto next = std::make_unique<Option>(*game);
  game->add_scene(std::move(out), std::move(next), std::move(in));
}