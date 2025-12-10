#ifndef SPLASH_SCREENS_HPP
#define SPLASH_SCREENS_HPP

#include "SplashScreen.hpp"

class StudioSC : public SplashScreen
{
    
public:
    Game *game;
    StudioSC(Game &game,  Animation anim, double time=3);
    void handle_event(Event &event);
    void update();
    void on_finish() override;
};

class SDLSC : public SplashScreen
{
public:
    Game *game;
    SDLSC(Game &game,  Animation anim, double time=2);
    void handle_event(Event &event);
    void update();
    void on_finish() override;
};

#endif