// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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