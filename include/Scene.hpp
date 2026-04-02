#ifndef SCENE_HPP
#define SCENE_HPP
#include "Game.hpp"

class Game;
/**
 * class manage a scene, all update, draw, handle_event should be override
 */

class Scene {
public:
  Game& game; // FIXME: does this really need an unique_ptr? we know it need a game reference, but arnt there's a better way?
  Scene(Game &game);
  bool is_working();
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void handle_event(Event &event) = 0;
  virtual ~Scene();
};
#endif