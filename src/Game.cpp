#include "Game.hpp"
#include "SceneTransition.hpp"

Game::Game() : in(nullptr), out(nullptr), next(nullptr), gameactive(true) {}

Scene *Game::current_scene() {
  return scene_list.empty() ? nullptr : scene_list.back().get();
}
bool Game::out_transitioning() { return bool(out); }
bool Game::in_transitioning() { return in and !out; }
// clear all on stack scene and go to scene
void Game::clear_scene(std::unique_ptr<SceneTransition> out,
                       std::unique_ptr<Scene> scene,
                       std::unique_ptr<SceneTransition> in) {
  command = CLEAR;
  out = std::move(out);
  next = std::move(scene);
  in = std::move(in);
}
// completely goback
void Game::remove_scene(std::unique_ptr<SceneTransition> out,
                        std::unique_ptr<SceneTransition> in) {
  if (scene_list.size() > 0) {
    command = REMOVE;
    in = std::move(in);
    out = std::move(out);
  }
}
// remove a scene and add another
void Game::pop_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  if (scene_list.size() > 0) {
    out = std::move(out);
    in = std::move(in);
    next = std::move(next);
    command = POP;
  }
}
void Game::add_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  out = std::move(out);
  next = std::move(scene);
  in = std::move(in);
  command = ADD;
}

// template<class T1, class T2, class T3>
// void Game::add_scene(T1 *out, T2 *scene, T3 *in)
// {
//     out = out;
//     next = scene;
//     in = in;
// }
// template<class T1, class T2, class T3>
// void Game::pop_scene(T1 *out, T2 *next, T3 *in)
// {
//     if (scene_list.size() > 0) {
//         out = out;
//         in = in;
//         next = next;
//     }
// }