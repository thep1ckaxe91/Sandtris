#include "QuitButton.hpp"
#include "Game.hpp"
#include "engine.hpp"

QuitButton::QuitButton(Game &g) : game(&g) {
  set_images(game->images.quit_button_idle,
             game->images.quit_button_hover,
             game->images.quit_button_click);
}

void QuitButton::handle_event(const Event &event) {
  Button::handle_event(event);
}
void QuitButton::on_click() {
  sdlgame::quit();
  exit(0);
}
void QuitButton::update() { Button::update(); }
