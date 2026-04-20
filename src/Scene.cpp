#include "Scene.hpp"

Scene::Scene(Game &game) : game(game) {}
bool Scene::is_working() { return this == game.current_scene(); };
