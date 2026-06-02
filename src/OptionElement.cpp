#include "OptionElement.hpp"
#include "SaveData.hpp"

using namespace std::string_literals;

SFXVolumeSlider::SFXVolumeSlider(Game &g, Vector2 start_pos, float start_val,
                                 float length, float max_val)
    : Slider(start_pos, start_val, length, max_val), game(g) {
  set_color("white"s, "white"s, "gray"s);
  set_label("SFX Volume: "s, "white"s);
}
void SFXVolumeSlider::update() { Slider::update(); }
void SFXVolumeSlider::handle_event(const Event &event) {
  Slider::handle_event(event);
}
void SFXVolumeSlider::draw() {
  game.m_window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game.m_window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::line(game.m_window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::rect(game.m_window, nob_color, nob);
}
void SFXVolumeSlider::on_change_value() {
  game.audio_manager.set_sfx_volume(value / max_value);
}

MusicVolumeSlider::MusicVolumeSlider(Game &g, Vector2 start_pos, float start_val,
                                     float length, float max_val)
    : Slider(start_pos, start_val, length, max_val), game(g) {
  set_color("white"s, "white"s, "gray"s);
  set_label("Music Volume: "s, "white"s);
}
void MusicVolumeSlider::update() { Slider::update(); }
void MusicVolumeSlider::handle_event(const Event &event) {
  Slider::handle_event(event);
}
void MusicVolumeSlider::draw() {
  game.m_window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game.m_window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::line(game.m_window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::rect(game.m_window, nob_color, nob);
}
void MusicVolumeSlider::on_change_value() {
  game.audio_manager.set_music_volume(value / max_value);
}

FullscreenSlider::FullscreenSlider(Game &g, Vector2 start_pos, float start_val,
                                   float length, float max_val)
    : Slider(start_pos, start_val, length, max_val), game(g) {
  set_color("white"s, "orange"s, "saddle brown"s);
  set_label("Fullscreen :"s, "white"s);
}
void FullscreenSlider::update() {
  nob.setCenter(topleft + Vector2(value * slide_length / max_value, 0));
}
void FullscreenSlider::handle_event(const Event &event) {
  Slider::handle_event(event);
}
void FullscreenSlider::draw() {
  game.m_window.blit(label_surf, label_rect.getTopLeft());
  sdlgame::draw::line(game.m_window, value_color, topleft,
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::line(game.m_window, no_value_color,
                      topleft + Vector2(slide_length, 0),
                      topleft + Vector2(slide_length, 0) * (value / max_value));
  sdlgame::draw::rect(game.m_window, nob_color, nob);
}
void FullscreenSlider::on_change_value() {
  value = (value == 0 ? max_value : 0);
  if (value != max_value) {
    std::pair<int, int> reso = load_window_info().second;
    if (reso.first == 0) {
      sdlgame::display::maximize();
    } else {
      sdlgame::display::set_window_size(reso.first, reso.second);
    }
  } else {
    sdlgame::display::fullscreen_desktop();
  }
}
