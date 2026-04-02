#include "OptionElement.hpp"
#include "SaveData.hpp"
SFXVolumeSlider::SFXVolumeSlider(Game &game, Vector2 topleft, float val,
                                 float length, float max_val)
    : Slider(topleft, val, length, max_val) {

  game = &game;
  set_color("white", "white", "gray");
  set_label("SFX Volume: ", "white");
}
SFXVolumeSlider::SFXVolumeSlider() = default;
void SFXVolumeSlider::update() { Slider::update(); }
void SFXVolumeSlider::handle_event(Event &event) {
  Slider::handle_event(event);
}
void SFXVolumeSlider::draw() {
  game->window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game->window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::line(game->window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::rect(game->window, nob_color, nob);
}
void SFXVolumeSlider::on_change_value() {
  game->audio_manager.set_sfx_volume(value / max_value);
}

MusicVolumeSlider::MusicVolumeSlider(Game &game, Vector2 topleft, float val,
                                     float length, float max_val)
    : Slider(topleft, val, length, max_val) {

  game = &game;
  set_color("white", "white", "gray");
  set_label("Music Volume: ", "white");
}
MusicVolumeSlider::MusicVolumeSlider() = default;
void MusicVolumeSlider::update() { Slider::update(); }
void MusicVolumeSlider::handle_event(Event &event) {
  Slider::handle_event(event);
}
void MusicVolumeSlider::draw() {
  game->window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game->window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::line(game->window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::rect(game->window, nob_color, nob);
}
void MusicVolumeSlider::on_change_value() {
  game->audio_manager.set_music_volume(value / max_value);
}

FullscreenSlider::FullscreenSlider(Game &game, Vector2 topleft, float value,
                                   float length, float max_value)
    : Slider(topleft, value, length, max_value) {
  game = &game;
  set_color("white", "orange", "saddle brown");
  set_label("Fullscreen :", "white");
}
FullscreenSlider::FullscreenSlider() = default;
void FullscreenSlider::update() {
  nob.setCenter(
      topleft +
      Vector2(value * slide_length / max_value, 0));
}
void FullscreenSlider::handle_event(Event &event) {
  Slider::handle_event(event);
}
void FullscreenSlider::draw() {
  game->window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game->window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::line(game->window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) *
                                    (value / max_value));
  sdlgame::draw::rect(game->window, nob_color, nob);
}
void FullscreenSlider::on_change_value() {
  value = (value == 0 ? max_value : 0);
  if (value != max_value) {
    std::pair<int, int> reso = load_window_info().second;
    if (reso.first == 0) {
      sdlgame::display::maximize();
    } else {
      sdlgame::display::set_window_size(reso.first, reso.second);
    } // cout << "call restore" << endl;
  } else {
    sdlgame::display::fullscreen_desktop();
    // cout << "call fullscreen" << endl;
  }
}