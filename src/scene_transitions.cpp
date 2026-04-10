#include "scene_transitions.hpp"
using Event = sdlgame::event::Event;
using Rect = rect::Rect;
using Vector2 = math::Vector2;
using Surface = sdlgame::surface::Surface;
using Color = sdlgame::color::Color;
using Sound = sdlgame::mixer::Sound;
using Channel = sdlgame::mixer::Channel;
using Font = sdlgame::font::Font;

OutSwipeDown::OutSwipeDown(double time) : SceneTransition(time) {
  vel = cur_height = 0;
  accelerate = (sdlgame::display::get_height() * 2 / (time * time));
}
void OutSwipeDown::update(double delta_time) {
  vel += accelerate * delta_time;
  time -= delta_time;
  if (time <= 0)
    isDone = 1;
  // cout << vel << " " << accelerate << " " << delta_time << endl;
  cur_height += vel * delta_time;
}
void OutSwipeDown::draw() {
  sdlgame::draw::rect(
      sdlgame::display::get_surf(), "black",
      Rect(0.0, 0.0, sdlgame::display::get_width(), cur_height));
}
InSwipeDown::InSwipeDown(double time) : SceneTransition(time) {
  vel = cur_height = 0;
  accelerate = (sdlgame::display::get_height() * 2) / time / time;
}
void InSwipeDown::update(double delta_time) {
  vel += accelerate * delta_time;
  time -= delta_time;
  if (time <= 0)
    isDone = 1;

  cur_height += vel * delta_time;
}
void InSwipeDown::draw() {
  sdlgame::draw::rect(sdlgame::display::get_surf(), "black",
                      Rect(0.0, cur_height, sdlgame::display::get_width(),
                           sdlgame::display::get_height()));
}

OutFade::OutFade(double time) : SceneTransition(time) {
  mask =
      Surface(sdlgame::display::get_width(), sdlgame::display::get_height());
  cur_color = Color("none");
  mask.fill(cur_color);
  vel = 255 / time;
  cur_alpha = 0;
}
void OutFade::update(double delta_time) {
  cur_alpha += vel * delta_time;
  cur_color.a = uint8_t(cur_alpha);
  time -= delta_time;
  mask.fill(cur_color);
  if (time <= 0) {
    isDone = 1;
  }
}
void OutFade::draw() {
  sdlgame::display::get_surf().blit(mask, Vector2());
}

InFade::InFade(double time) : SceneTransition(time) {
  mask =
      Surface(sdlgame::display::get_width(), sdlgame::display::get_height());
  cur_color = Color("black");
  mask.fill(cur_color);
  vel = -255 / time;
  cur_alpha = 255;
}
void InFade::update(double delta_time) {
  cur_alpha += vel * delta_time;
  cur_color.a = uint8_t(cur_alpha);
  time -= delta_time;
  mask.fill(cur_color);
  if (time <= 0) {
    isDone = 1;
  }
}
void InFade::draw() {
  sdlgame::display::get_surf().blit(mask, Vector2());
}
