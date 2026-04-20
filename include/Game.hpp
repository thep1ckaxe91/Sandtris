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
  std::unique_ptr<SceneTransition> m_in;
  std::unique_ptr<SceneTransition> m_out;
  std::unique_ptr<Scene> m_next;
  SceneCommand m_command;
  bool m_gameactive;

public:
  std::vector<std::unique_ptr<Scene>> m_scene_list;
  Images m_images;
  AudioManager m_audio_manager;
  sdlgame::surface::Surface
      m_window; // window is an actual texture getting drawn on
  sdlgame::surface::Surface
      m_window_object; // a nullptr texture surface, represent the actual window
  sdlgame::time::Clock m_clock;
  Vector2 m_window_draw_offset; // TODO: this is just a quick patch to be able to create a screen shake effect, there must be a cleaner way
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
