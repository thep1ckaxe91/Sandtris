#include "Scene.hpp"

Scene::Scene(Game &game)
{
    this->game = &game;
}
Scene::Scene(){this->game = nullptr;}
Scene::~Scene() = default;
bool Scene::is_working()
{
    return this == this->game->current_scene();
};