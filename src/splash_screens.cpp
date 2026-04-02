#include "splash_screens.hpp"
#include "MainMenu.hpp"
#include "SceneTransition.hpp"
#include "scene_transitions.hpp"
#include <memory>

SDLSC::SDLSC(Game &game, Animation anim, double time)
    : SplashScreen(game, time, anim) {}
void SDLSC::handle_event(Event &event) { SplashScreen::handle_event(event); }
void SDLSC::update() { SplashScreen::update(); }
void SDLSC::on_finish() {
  auto out = std::make_unique<OutFade>(1);
  auto in = std::make_unique<InFade>(1);
  std::unique_ptr<Scene> next = std::make_unique<MainMenu>(*game);
  game->pop_scene(std::move(out), std::move(next), std::move(in));
}

StudioSC::StudioSC(Game &game, Animation anim, double time)
    : SplashScreen(game, time, anim) {
  game->audio_manager.sfx.soft_wind_blow.play();
}
void StudioSC::handle_event(Event &event) { SplashScreen::handle_event(event); }
void StudioSC::update() { SplashScreen::update(); }
void StudioSC::on_finish() {
  Animation sdlsc(*game, 30, 1);
  sdlsc.load(base_path + "assets/animations/splash/sdl/");
  sdlsc.set_default(sdlsc.frames.back());
  sdlsc.play();
  auto out = std::make_unique<OutFade>(1);
  auto in = std::make_unique<InFade>(1);
  std::unique_ptr<Scene> next = std::make_unique<SDLSC>(*game, sdlsc, 5);
  game->pop_scene(std::move(out), std::move(next), std::move(in));
  game->audio_manager.sfx.soft_wind_blow.fadeout(1000);
}
