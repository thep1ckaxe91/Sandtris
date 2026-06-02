#include "Game.hpp"
#include "SceneTransition.hpp"
#include "Scene.hpp"

Game::Game() : m_command(SceneCommand::NONE), m_gameactive(true) {}

std::optional<const Scene *const> Game::current_scene() const {
  return m_scene_list.empty() ? std::nullopt : std::optional<const Scene *const>(m_scene_list.back().get());
}

bool Game::out_transitioning() { return bool(m_out); }
bool Game::in_transitioning() { return m_in && !m_out; }

void Game::clear_scene(std::unique_ptr<SceneTransition> out,
                       std::unique_ptr<Scene> scene,
                       std::unique_ptr<SceneTransition> in) {
  m_command = SceneCommand::CLEAR;
  m_out = std::move(out);
  m_next = std::move(scene);
  m_in = std::move(in);
}

void Game::remove_scene(std::unique_ptr<SceneTransition> out,
                        std::unique_ptr<SceneTransition> in) {
  if (!m_scene_list.empty()) {
    m_command = SceneCommand::REMOVE;
    m_in = std::move(in);
    m_out = std::move(out);
  }
}

void Game::pop_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  if (!m_scene_list.empty()) {
    m_command = SceneCommand::POP;
    m_out = std::move(out);
    m_in = std::move(in);
    m_next = std::move(scene);
  }
}

void Game::add_scene(std::unique_ptr<SceneTransition> out,
                     std::unique_ptr<Scene> scene,
                     std::unique_ptr<SceneTransition> in) {
  m_command = SceneCommand::ADD;
  m_out = std::move(out);
  m_next = std::move(scene);
  m_in = std::move(in);
}

Game::~Game() = default;
