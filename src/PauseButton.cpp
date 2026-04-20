#include "PauseButton.hpp"
#include "Pause.hpp"
#include "scene_transitions.hpp"
PauseButton::PauseButton(Game &game) {
  game = &game;
  set_images(game->m_images.pause_button_idle,
                   game->m_images.pause_button_hover,
                   game->m_images.pause_button_click);
  rect = (*image).get_rect();
}
PauseButton::PauseButton() = default;
void PauseButton::update() { Button::update(); }
void PauseButton::handle_event(const Event &event) { Button::handle_event(event); }
void PauseButton::on_click() {
  auto out = std::make_unique<OutFade>(1);
  auto in = std::make_unique<InFade>(1);
  auto next = std::make_unique<Pause>(*game);
  game->add_scene(std::move(out), std::move(next), std::move(in));
}