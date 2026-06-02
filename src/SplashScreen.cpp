#include "SplashScreen.hpp"

SplashScreen::SplashScreen(Game &game, double time, std::shared_ptr<Animation> anim)
    : Scene(game), splash(anim), time(time), done(false) {}

void SplashScreen::play() { splash->play(); }

void SplashScreen::handle_event(const Event &event) {
  if (event.type == sdlgame::MOUSEBUTTONDOWN) {
    on_finish();
    done = true;
  }
}
void SplashScreen::update() {
  if (splash->is_playing()) {
    splash->update();
    time -= game.m_clock.delta_time().count();
    if (time <= 0) {
      splash->pause();
    }
  } else {
    if (!done)
      on_finish();
    done = true;
  }
}
void SplashScreen::draw() { game.m_window.blit(splash->get_image(), Vector2()); }
SplashScreen::~SplashScreen() = default;
