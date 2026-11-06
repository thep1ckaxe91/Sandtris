#include "splash_screens.hpp"
#include "MainMenu.hpp"
#include "scene_transitions.hpp"
#include <memory>

SDLSC::SDLSC(Game &gameInstance, std::unique_ptr<Animation> anim,
             double duration)
    : SplashScreen(gameInstance, duration, std::move(anim)) {}
void SDLSC::handle_event(const sdlgame::event::Event &event) {
  SplashScreen::handle_event(event);
}
void SDLSC::update() { SplashScreen::update(); }
void SDLSC::on_finish() {
  auto out = std::make_unique<OutFade>(1);
  auto in = std::make_unique<InFade>(1);
  std::unique_ptr<Scene> next = std::make_unique<MainMenu>(game);
  game.pop_scene(std::move(out), std::move(next), std::move(in));
}

StudioSC::StudioSC(Game &gameInstance, std::unique_ptr<Animation> anim,
                   double duration)
    : SplashScreen(gameInstance, duration, std::move(anim)) {
  gameInstance.audio_manager.sfx.soft_wind_blow.play();
}
void StudioSC::handle_event(const sdlgame::event::Event &event) {
  SplashScreen::handle_event(event);
}
void StudioSC::update() { SplashScreen::update(); }
void StudioSC::on_finish() {
  auto sdl_anim = std::make_unique<Animation>(game, 30, true);
  sdl_anim->load(base_path / "assets" / "animations" / "splash" / "sdl");
  sdl_anim->set_default_image(sdl_anim->get_frames().back());
  sdl_anim->play();
  auto out = std::make_unique<OutFade>(1);
  auto in = std::make_unique<InFade>(1);
  std::unique_ptr<Scene> next =
      std::make_unique<SDLSC>(game, std::move(sdl_anim), 5);
  game.pop_scene(std::move(out), std::move(next), std::move(in));
  game.audio_manager.sfx.soft_wind_blow.fadeout(1000);
}
