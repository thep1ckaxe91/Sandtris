#include "MenuButton.hpp"
#include "MainMenu.hpp"
#include "scene_transitions.hpp"
#include <memory>

MenuButton::MenuButton(Game &g) : game(&g) {
  set_images(game->images.menu_button_idle,
             game->images.menu_button_hover,
             game->images.menu_button_click);
}
void MenuButton::handle_event(const Event &event) { Button::handle_event(event); }
void MenuButton::on_click() {
  auto out = std::make_unique<OutSwipeDown>();
  auto in = std::make_unique<InSwipeDown>();
  auto next = std::make_unique<MainMenu>(*game);
  game->clear_scene(std::move(out), std::move(next), std::move(in));
}
void MenuButton::update() { Button::update(); }
