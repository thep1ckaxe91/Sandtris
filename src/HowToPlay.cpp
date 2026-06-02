#include "HowToPlay.hpp"
#include "constant.hpp"

HowToPlay::HowToPlay(Game &game) : Scene(game) {
  back_button = std::make_shared<BackButton>(game);
  back_button->get_rect().setTopLeft(bb_pos);
  height_pos = 0;
}

void HowToPlay::handle_event(const Event &event) {
  back_button->handle_event(event);
  if (event.type == sdlgame::MOUSEWHEEL) {
    height_pos += event["y"] * 4;
    height_pos = sdlgame::math::clamp(height_pos, -145.0, 0.0);
  }
}
void HowToPlay::update() { back_button->update(); }

void HowToPlay::draw() {
  game.m_window.blit(*game.images.instruction_image, Vector2(0, height_pos));
  game.m_window.blit(back_button->get_image(), bb_pos);
}
