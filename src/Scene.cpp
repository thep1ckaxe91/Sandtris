#include "Scene.hpp"

Scene::Scene(Game &game) : game(game) {}
Scene::~Scene() = default;
bool Scene::is_working() { return this == game.current_scene(); };