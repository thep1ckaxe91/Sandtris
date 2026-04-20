#include "Game.hpp"
#include "SceneTransition.hpp"

Game::Game() : m_in(nullptr), m_out(nullptr), m_next(nullptr), m_gameactive(true) {}

Scene *Game::current_scene() {
  return m_scene_list.empty() ? nullptr : m_scene_list.back().get();
}
bool Game::out_transitioning() { return bool(m_out); }
bool Game::in_transitioning() { return m_in and !m_out; }
// clear all on stack scene and go to scene
void Game::clear_scene(std::unique_ptr<SceneTransition> out,
                       std::unique_ptr<Scene> scene,
                       std::unique_ptr<SceneTransition> in) {
  this->m_command = CLEAR;
  this->m_out = std::move(out);
  this->m_next = std::move(scene);
  this->m_in = std::move(in);
}
// completely goback
void Game::remove_scene(std::unique_ptr<SceneTransition> out,
                        std::unique_ptr<SceneTransition> in) {
  if (m_scene_list.size() > 0) {
    this->m_command = REMOVE;
    this->m_in = std::move(in);
    this->m_out = std::move(out);
  }
}
// remove a scene and add another
void Game::pop_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  if (m_scene_list.size() > 0) {
    this->m_out = std::move(out);
    this->m_in = std::move(in);
    this->m_next = std::move(m_next);
    this->m_command = POP;
  }
}
void Game::add_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  this->m_out = std::move(out);
  this->m_next = std::move(scene);
  this->m_in = std::move(in);
  this->m_command = ADD;
}