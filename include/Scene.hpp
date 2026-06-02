#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include "event.hpp"

using Event = sdlgame::event::Event;

class Game;

/**
 * class manage a scene, all update, draw, handle_event should be override
 */
class Scene {
public:
  Game &game; // FIXME: the Game reference is really drilling through every source file lol 
  // figure out a way to get this off, maybe utilize event bus more, localize

  Scene(Game &);
  virtual ~Scene() = default;

  Scene(Scene &&) = delete;
  Scene(const Scene &) = delete;
  void operator=(Scene &&) = delete;
  void operator=(const Scene &) = delete;

  bool is_working();
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void handle_event(const Event &event) = 0;
};
#endif
