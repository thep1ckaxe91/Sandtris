#include "SplashScreen.hpp"
#include <memory>
#include <sdlgame/constants.hpp>
#include <sdlgame/math.hpp>

using sdlgame::math::Vector2;

SplashScreen::SplashScreen(Game &gameInstance, double duration,
                           std::unique_ptr<Animation> anim)
    : Scene(gameInstance), splash(std::move(anim)), time(duration), done(false) {}

void SplashScreen::play() { splash->play(); }

void SplashScreen::handle_event(const sdlgame::event::Event &event) {
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
void SplashScreen::draw() {
  game.m_window.blit(splash->get_image(), Vector2());
}
SplashScreen::~SplashScreen() = default;
