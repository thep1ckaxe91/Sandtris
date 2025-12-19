// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

#include "engine/engine.hpp"
#include <bits/stdc++.h>
/**
 * @brief Slider is expect to inherit.
 * Call set color and overwrite draw and on_change_value should be good enough
 * 
 * 
 */
class Slider
{
protected:
    float value;
    Rect nob;
    float slide_length;
    float max_value;
    Vector2 topleft;
    bool holding;
    Color nob_color;
    Color value_color;
    Color no_value_color;
    Font label_font;
    Surface label_surf;
    Rect label_rect;
public:
    Slider(Vector2 topleft, float value=1, float slide_length=48, float max_value=1);
    Slider();
    void set_label(std::string text, Color color);
    void set_color(Color nob, Color valid, Color invalid);
    virtual void update();
    virtual void handle_event(Event &event);
    virtual void draw()=0;
    virtual void on_change_value()=0;
};

