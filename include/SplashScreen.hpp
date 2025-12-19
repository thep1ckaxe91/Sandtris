// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "Animation.hpp"
#include "Scene.hpp"
#include "scene_transitions.hpp"
class SplashScreen : public Scene
{
private:
public:
    Animation splash;
    double time;
    bool done;
    /**
     * @brief Construct a new Splash Screen object
     * 
     * @param game 
     * @param time total time for splash screen from in transition start and out transition end;
     */
    SplashScreen(Game &game, double time,Animation &anim);
    SplashScreen();
    void play();
    virtual void on_finish()=0;
    virtual void handle_event(Event &event);
    virtual void update();
    void draw();
    ~SplashScreen();
};

