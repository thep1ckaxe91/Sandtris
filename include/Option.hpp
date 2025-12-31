#ifndef OPTION_HPP
#define OPTION_HPP

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
#endif