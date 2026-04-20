#include "CreditButton.hpp"
#include "Credit.hpp"
#include "scene_transitions.hpp"
#include <memory>
CreditButton::CreditButton(Game &game) {
  game = &game;
  set_images(game->m_images.credit_button_idle,
             game->m_images.credit_button_hover,
             game->m_images.credit_button_click);
  rect = (*image).get_rect();
}
CreditButton::CreditButton() = default;
void CreditButton::update() { Button::update(); }
void CreditButton::handle_event(const Event &event) { Button::handle_event(event); }
void CreditButton::on_click() {
  auto in = std::make_unique<InFade>(1);
  auto out = std::make_unique<OutFade>(1);
  auto next = std::make_unique<Credit>(*game);
  game->add_scene(std::move(out), std::move(next), std::move(in));
}