#ifndef SFX_HPP
#define SFX_HPP

//Load all sfx for use here
#include "engine/mixer.hpp"
#include "constant.hpp"
const std::string sfx_path = "data/audio/sfx/";
class SFX 
{
public:
    Sound button_click;
    Sound button_hover;
    Sound count_down;
    Sound count_down_start;
    Sound game_over;
    Sound merge;
    Sound rotate;
    Sound scoring;
    Sound transition_in;
    Sound transition_out;
    Sound soft_wind_blow;
    SFX();
    void load();
};

#endif