// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "Scene.hpp"
#include "StartButton.hpp"
#include "QuitButton.hpp"
#include "CreditButton.hpp"
#include "engine/engine.hpp"
#include "PBButton.hpp"
#include "HTPButton.hpp"
#include "OptionButton.hpp"
#include "ResumeButton.hpp"
class MainMenu : public Scene
{
public:
    StartButton start_button;
    QuitButton quit_button;
    CreditButton credit_button;
    PBButton pb_button;
    HTPButton htp_button;
    OptionButton option_button;
    ResumeButton resume_button;
    bool can_resume;
    MainMenu(Game &game);
    void handle_event(Event &event);
    void update();
    void draw();
    ~MainMenu();
};

