#include "Game.hpp"
#include "engine/engine.hpp"
Game::Game()
{
    gameactive = 1;
    in = out = nullptr;
    next = nullptr;
}
Scene * Game::current_scene()
{
    return scene_list.empty() ? nullptr : this->scene_list.back();
}
bool Game::out_transitioning()
{
    return out;
}
bool Game::in_transitioning()
{
    return in and !out;
}
//clear all on stack scene and go to scene
void Game::clear_scene(SceneTransition *out, Scene *scene, SceneTransition *in)
{
    this->command = CLEAR;
    this->out = out;
    this->next = scene;
    this->in = in;
}
// completely goback
void Game::remove_scene(SceneTransition* out, SceneTransition* in)
{
    if (this->scene_list.size() > 0)
    {
        this->command = REMOVE;
        this->in = in;
        this->out = out;
    }
}
// remove a scene and add another
void Game::pop_scene(SceneTransition* out, Scene* next, SceneTransition* in)
{
    if (scene_list.size() > 0) {
        this->out = out;
        this->in = in;
        this->next = next;
        this->command = POP;
    }
}
void Game::add_scene(SceneTransition *out, Scene *scene, SceneTransition *in)
{
    this->out = out;
    this->next = scene;
    this->in = in;
    this->command = ADD;
}

// template<class T1, class T2, class T3>
// void Game::add_scene(T1 *out, T2 *scene, T3 *in)
// {
//     this->out = out;
//     this->next = scene;
//     this->in = in;
// }
// template<class T1, class T2, class T3>
// void Game::pop_scene(T1 *out, T2 *next, T3 *in)
// {
//     if (scene_list.size() > 0) {
//         this->out = out;
//         this->in = in;
//         this->next = next;
//     } 
// }