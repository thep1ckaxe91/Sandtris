#ifndef OPTION_ELEMENT_HPP
#define OPTION_ELEMENT_HPP
#include "Slider.hpp"
#include "Game.hpp"
using namespace std;

class SFXVolumeSlider : public Slider
{
public:
    Game *game;
    SFXVolumeSlider(Game &game, Vector2 topleft, float value, float length, float max_value);
    SFXVolumeSlider();
    void update();
    void handle_event(Event &event);
    void draw();
    void on_change_value();
};

class MusicVolumeSlider : public Slider
{
public:
    Game *game;
    MusicVolumeSlider(Game &game, Vector2 topleft, float value, float length, float max_value);
    MusicVolumeSlider();
    void update();
    void handle_event(Event &event);
    void draw();
    void on_change_value();
};

class FullscreenSlider : public Slider
{
public:
    Game *game;
    FullscreenSlider(Game &game, Vector2 topleft, float value, float length, float max_value);
    FullscreenSlider();
    void update();
    void handle_event(Event &event);
    void draw();
    void on_change_value();
};

// class OptionElement
// {

// public:
//     string label;
//     Surface label_surf;
//     Font label_font;
//     Vector2 topleft;
//     Slider *setter;
//     OptionElement(Vector2 topleft, string name, float value, float max_value);
//     OptionElement();
//     void update();
//     void handle_event(Event &event);
//     void draw();
// };

#endif