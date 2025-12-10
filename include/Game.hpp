#ifndef GAME_HPP
#define GAME_HPP
#include "engine/engine.hpp"
#include "Images.hpp"
#include "Scene.hpp"
#include "SceneTransition.hpp"
#include "AudioManager.hpp"
using namespace std;
class Scene;
/**
 * This class have to be inherit and override

 * This class represent the entire game itself

 * in and out transition memory management is your responsibility
*/
class Game
{
protected:
    bool gameactive;
    SceneTransition *in;
    SceneTransition *out;
    Scene *next;
    SceneCommand command;
public:
    std::vector<Scene *> scene_list;
    Images images;
    AudioManager audio_manager;
    sdlgame::surface::Surface window;
    sdlgame::surface::Surface window_object;
    sdlgame::time::Clock clock;
    Vector2 window_draw_offset;
    Game();
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
    Scene *current_scene();
    bool out_transitioning();
    bool in_transitioning();
    // template <class T1, class T2, class T3>
    // void add_scene(T1 *out, T2 *next, T3 *in);
    void add_scene(SceneTransition *out, Scene *scene, SceneTransition *in);
    // completely goback
    void remove_scene(SceneTransition* out, SceneTransition* in);
    void clear_scene(SceneTransition *out, Scene *scene, SceneTransition *in);
    // remove a scene and add another
    // template <class T1, class T2, class T3>
    // void pop_scene(T1* out, T2* next, T3* in);
    void pop_scene(SceneTransition* out, Scene* next, SceneTransition* in);
};
#endif