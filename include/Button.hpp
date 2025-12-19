// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "engine/engine.hpp"
class Button : public sdlgame::sprite::Sprite
{
public:
    Surface *idle;
    Surface *hover;
    Surface *click;
    bool hovering, prev_hovered;
    Button();
    virtual void on_click()=0;
    void set_images(Surface &idle, Surface &hover, Surface &click);
    virtual void handle_event(Event &event);
    virtual void update();

};

