#include "SplashScreen.hpp"

SplashScreen::SplashScreen(Game &game, double time,
                           const std::shared_ptr<Animation> &anim)
    : Scene(game), m_animation(anim), m_time(time) {}

void SplashScreen::play() { m_animation->play(); }
void SplashScreen::handle_event(const Event &event) {
  if (event.type == sdlgame::MOUSEBUTTONDOWN) {
    on_finish();
    m_done = 1;
  }
}
void SplashScreen::update() {
  if (m_animation->is_playing()) {
    m_animation->update();
    // cout << game->clock.delta_time().count() << endl;
    m_time -= game.m_clock.delta_time().count();
    // cout << time << endl;
    if (m_time <= 0) {
      m_animation->pause();
    }
  } else {
    if (!m_done)
      on_finish();
    m_done = 1;
  }
}
void SplashScreen::draw() { game.m_window.blit(m_animation->get_image(), {}); }