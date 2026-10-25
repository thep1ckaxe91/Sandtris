#pragma once
#ifndef SCENE_TRANSITIONS_HPP
#define SCENE_TRANSITIONS_HPP
#include "SceneTransition.hpp"
#include <sdlgame/surface.hpp>
#include <sdlgame/color.hpp>

class OutSwipeDown : public SceneTransition {
public:
  double accelerate;
  double vel;
  double cur_height;
  OutSwipeDown(double time = 2);
  void update(double delta_time);
  void draw();
};
class InSwipeDown : public SceneTransition {
public:
  double accelerate;
  double vel;
  double cur_height;
  InSwipeDown(double time = 2);
  void update(double delta_time);
  void draw();
};

class OutFade : public SceneTransition {
public:
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_TARGET> mask;
  double vel, cur_alpha;
  sdlgame::color::Color cur_color;
  OutFade(double time = 2);
  void update(double delta_time);
  void draw();
};
class InFade : public SceneTransition {
public:
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_TARGET> mask;
  double vel, cur_alpha;
  sdlgame::color::Color cur_color;
  InFade(double time = 2);
  void update(double delta_time);
  void draw();
};
#endif