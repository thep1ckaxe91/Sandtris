#include "Option.hpp"
#include "SaveData.hpp"

Option::Option(Game &_game) : Scene(_game) {
  sfx_slider = std::make_shared<SFXVolumeSlider>(
      game, Vector2(80, 32), game.audio_manager.get_sfx_volume(), 48, 1);
  music_slider = std::make_shared<MusicVolumeSlider>(
      game, Vector2(80, 64), game.audio_manager.get_music_volume(), 48, 1);
  fs_slider = std::make_shared<FullscreenSlider>(
      game, Vector2(80, 96), sdlgame::display::is_fullscreen(), 5, 1);
  back_button = std::make_shared<BackButton>(game);
  back_button->get_rect().setBottomRight(RESOLUTION_WIDTH - 2,
                                          RESOLUTION_HEIGHT - 2);
}

void Option::update() {
  sfx_slider->update();
  music_slider->update();
  back_button->update();
  fs_slider->update();
}
void Option::handle_event(const Event &event) {
  sfx_slider->handle_event(event);
  music_slider->handle_event(event);
  back_button->handle_event(event);
  fs_slider->handle_event(event);
}
void Option::draw() {
  sfx_slider->draw();
  music_slider->draw();
  fs_slider->draw();
  game.m_window.blit(back_button->get_image(),
                     back_button->get_rect().getTopLeft());
}
