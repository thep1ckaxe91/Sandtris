#include "PBButton.hpp"
#include "PersonalBest.hpp"
#include "scene_transitions.hpp"
#include <memory>
PBButton::PBButton(Game &game) {
  game = &game;
  set_images(game->m_images.pb_button_idle,
                   game->m_images.pb_button_hover,
                   game->m_images.pb_button_click);
  rect = (*image).get_rect();
}
PBButton::PBButton() = default;
void PBButton::on_click() {
  auto in = std::make_unique<InFade>(1);
  auto out = std::make_unique<OutFade>(1);
  auto next = std::make_unique<PersonalBest>(*game);

  game->add_scene(std::move(out), std::move(next), std::move(in));
}

void PBButton::update() { Button::update(); }

void PBButton::handle_event(const Event &event) { Button::handle_event(event); }