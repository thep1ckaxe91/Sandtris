#include "SFX.hpp"

SFX::SFX() = default;
void SFX::load()
{
    button_click = Sound(base_path + sfx_path + "button_click.wav");
    button_hover = Sound(base_path + sfx_path + "button_hover.wav");
    count_down = Sound(base_path + sfx_path + "count_down.wav");
    count_down_start = Sound(base_path + sfx_path + "count_down_start.wav");
    game_over = Sound(base_path + sfx_path + "game_over.wav");
    merge = Sound(base_path + sfx_path + "merge.wav");
    rotate = Sound(base_path + sfx_path + "rotate.wav");
    scoring = Sound(base_path + sfx_path + "scoring.wav");
    transition_in = Sound(base_path + sfx_path + "transition_in.wav");
    transition_out = Sound(base_path + sfx_path + "transition_out.wav");
    soft_wind_blow = Sound(base_path + sfx_path + "soft_wind_blow.wav");
}