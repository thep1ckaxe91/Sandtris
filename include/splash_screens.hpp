// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

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

