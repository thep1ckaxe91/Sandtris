#include "Slider.hpp"
#include "constant.hpp"

/**
 * @brief Construct a new Slider:: Slider object
 *
 * @param topleft start point of the slider, also be the mid left of the label
 * @param value current value of the slider
 * @param slide_length length of the slider
 * @param max_value 0 to max value is the value range
 * @param text text for the label
 */
Slider::Slider(Vector2 topleft, float value, float slide_length,
               float max_value)
    : nob(Rect{0, 0, 3, 3}), topleft(topleft),
      label_font(Font(font_path, FONT_SIZE)), value(value),
      slide_length(slide_length), max_value(max_value), holding(0) {
  set_label("default label", "white");
  set_color("white", "white", "gray");
  nob.setCenter(topleft + Vector2(value / max_value * slide_length, 0));
}
Slider::Slider() = default;
void Slider::set_label(std::string text, Color color) {
  label_surf = label_font.render(text, 0, color);
  label_rect = label_surf.get_rect();
  label_rect.setMidRight(topleft);
}
void Slider::update() {
  if (holding) {
    nob.setCenter(sdlgame::math::clamp(sdlgame::mouse::get_pos().x,
                                       topleft.x,
                                       topleft.x + slide_length),
                  topleft.y);
    value =
        (nob.getCenterX() - topleft.x) / slide_length * max_value;
  }
}
/**
 * @brief set color for each element of the nob
 *
 * @param nob color of the nob
 * @param valid color for the part that represent the total value
 * @param invalid color for the part that dont represent the value
 */
void Slider::set_color(Color nob, Color valid, Color invalid) {
  nob_color = nob;
  value_color = valid;
  no_value_color = invalid;
}
void Slider::handle_event(const Event &event) {
  if (event.type == sdlgame::MOUSEBUTTONDOWN and
      nob.collidepoint(sdlgame::mouse::get_pos())) {
    holding = 1;
  } else if (event.type == sdlgame::MOUSEBUTTONUP) {
    if (holding)
      on_change_value();
    holding = 0;
  }
}