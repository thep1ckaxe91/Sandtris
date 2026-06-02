#include "Pause.hpp"

using namespace std::string_literals;

Pause::Pause(Game &game) : Scene(game) {
  message_font = Font(font_path, FONT_SIZE);
  message_surf = message_font.render("Progress will be save", sdlgame::font::AntiAlias::SOLID, "white"s);
  message_rect = message_surf.get_rect();
  message_rect.setCenter(RESOLUTION_WIDTH / 2,
                         RESOLUTION_HEIGHT - message_rect.getHeight() / 2 - 2);
  menu_button = std::make_shared<MenuButton>(game);
  menu_button->get_rect().setCenter(55, 64);
  retry_button = std::make_shared<RetryButton>(game);
  retry_button->get_rect().setCenter(55, 64 + 16 + 2);
  back_button = std::make_shared<BackButton>(game);
  back_button->get_rect().setCenter(55, 64 + 4 + 32);
  option_button = std::make_shared<OptionButton>(game);
  option_button->get_rect().setCenter(102, 68);
}

void Pause::render_message(std::string new_message) {
  message_surf = message_font.render(new_message, sdlgame::font::AntiAlias::SOLID, "white"s);
  message_rect = message_surf.get_rect();
  message_rect.setCenter(RESOLUTION_WIDTH / 2,
                         RESOLUTION_HEIGHT - message_rect.getHeight() / 2 - 2);
}
void Pause::display_message() {
  game.m_window.blit(message_surf, message_rect.getTopLeft());
}
void Pause::update() {
  menu_button->update();
  if (menu_button->hovering and !menu_button->prev_hovered)
    render_message("Progress will be save");

  option_button->update();
  retry_button->update();
  back_button->update();
}

void Pause::handle_event(const Event &event) {
  menu_button->handle_event(event);
  option_button->handle_event(event);
  retry_button->handle_event(event);
  back_button->handle_event(event);
}
void Pause::draw() {
  game.m_window.blit(*game.images.pause_background, Vector2());
  game.m_window.blit(menu_button->get_image(), menu_button->get_rect().getTopLeft());
  game.m_window.blit(option_button->get_image(),
                     option_button->get_rect().getTopLeft());
  game.m_window.blit(retry_button->get_image(), retry_button->get_rect().getTopLeft());
  game.m_window.blit(back_button->get_image(), back_button->get_rect().getTopLeft());
  if (menu_button->hovering)
    display_message();
}
