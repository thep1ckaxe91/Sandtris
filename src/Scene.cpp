#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(Game &_game) : game(_game) {}
bool Scene::is_working() { return game.current_scene().has_value() && this == game.current_scene().value(); };
