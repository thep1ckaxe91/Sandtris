// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#include "Game.hpp"
#include "Scene.hpp"
#include "OptionElement.hpp"
#include "BackButton.hpp"
class Option : public Scene
{
public:
    BackButton back_button;
    SFXVolumeSlider sfx_slider;
    MusicVolumeSlider music_slider;
    FullscreenSlider fs_slider;
    Option(Game &game);
    Option();
    void update();
    void handle_event(Event &event);
    void draw();
};
