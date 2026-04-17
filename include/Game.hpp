#ifndef GAME_HPP
#define GAME_HPP
#include "AudioManager.hpp"
#include "Images.hpp"
#include "Scene.hpp"
#include "SceneTransition.hpp"
#include "constant.hpp"
#include "engine.hpp"

/**
 * This class have to be inherit and override

 * This class represent the entire game itself

 * in and out transition memory management is your responsibility
*/
class Game {
protected:
  std::unique_ptr<SceneTransition> in;
  std::unique_ptr<SceneTransition> out;
  std::unique_ptr<Scene> next;
  SceneCommand command;
  bool gameactive;

public:
  std::vector<std::unique_ptr<Scene>> scene_list;
  Images images;
  AudioManager audio_manager;
  sdlgame::surface::Surface
      window; // window is an actual texture getting drawn on
  sdlgame::surface::Surface
      window_object; // a nullptr texture surface, represent the actual window
  sdlgame::time::Clock clock;
  Vector2 window_draw_offset;
  Game();
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void run() = 0;
  Scene *current_scene();
  bool out_transitioning();
  bool in_transitioning();
  void add_scene(std::unique_ptr<SceneTransition> out,
                 std::unique_ptr<Scene> scene,
                 std::unique_ptr<SceneTransition> in);
  // completely goback
  void remove_scene(std::unique_ptr<SceneTransition> out,
                    std::unique_ptr<SceneTransition> in);
  void clear_scene(std::unique_ptr<SceneTransition> out,
                   std::unique_ptr<Scene> scene,
                   std::unique_ptr<SceneTransition> in);
  void pop_scene(std::unique_ptr<SceneTransition> out,
                 std::unique_ptr<Scene> scene,
                 std::unique_ptr<SceneTransition> in);
  virtual ~Game();
};
#endif
