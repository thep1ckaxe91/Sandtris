#include "Credit.hpp"
#include "constant.hpp"

Credit::Credit(Game &game) : Scene(game) {
  back_button = std::make_shared<BackButton>(game);
  back_button->get_rect().setTopLeft(bb_pos);
}

void Credit::handle_event(const Event &event) { back_button->handle_event(event); }
void Credit::update() { back_button->update(); }

void Credit::draw() {
  game.m_window.blit(*game.images.credit_image, Vector2());
  game.m_window.blit(back_button->get_image(), bb_pos);
}
