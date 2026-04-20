#include "HTPButton.hpp"
#include "HowToPlay.hpp"
#include "scene_transitions.hpp"
#include <memory>
HTPButton::HTPButton(Game &game) {
  game = &game;
  set_images(game->m_images.htp_button_idle,
             game->m_images.htp_button_hover,
             game->m_images.htp_button_click);
  rect = (*image).get_rect();
}
HTPButton::HTPButton() = default;
void HTPButton::update() { Button::update(); }
void HTPButton::handle_event(const Event &event) { Button::handle_event(event); }
void HTPButton::on_click() {
  auto in = std::make_unique<InFade>(1);
  auto out = std::make_unique<OutFade>(1);
  auto next = std::make_unique<HowToPlay>(*game);
  game->add_scene(std::move(out), std::move(next), std::move(in));
}