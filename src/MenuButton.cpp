#include "MenuButton.hpp"
#include "MainMenu.hpp"
#include "scene_transitions.hpp"
#include <memory>
MenuButton::MenuButton(Game &game) {
  game = &game;
  set_images(game->images.menu_button_idle,
                   game->images.menu_button_hover,
                   game->images.menu_button_click);
  rect = (*image).get_rect();
}
MenuButton::MenuButton() = default;
void MenuButton::handle_event(Event &event) { Button::handle_event(event); }
void MenuButton::on_click() {
  auto out = std::make_unique<OutSwipeDown>();
  auto in = std::make_unique<InSwipeDown>();
  auto next = std::make_unique<MainMenu>(*game);
  game->clear_scene(std::move(out), std::move(next), std::move(in));
}
void MenuButton::update() { Button::update(); }
