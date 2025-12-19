// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once
#include "engine/engine.hpp"
#include "SFX.hpp"
class AudioManager
{
private:
    float sfx_volume;
    float music_volume;
public:
    SFX sfx;
    AudioManager();
    void update();
    void handle_event(Event &event);
    void set_sfx_volume(float value);
    float get_sfx_volume();
    void set_music_volume(float value);
    float get_music_volume();
};

