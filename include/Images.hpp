#ifndef IMAGES_HPP
#define IMAGES_HPP
#include "engine/engine.hpp"

class Images
{
public:
    Surface start_button_idle;
    Surface start_button_hover;
    Surface start_button_click;
    
    Surface credit_button_idle;
    Surface credit_button_hover;
    Surface credit_button_click;

    Surface quit_button_idle;
    Surface quit_button_hover;
    Surface quit_button_click;

    Surface back_button_idle;
    Surface back_button_hover;
    Surface back_button_click;

    Surface menu_button_idle;
    Surface menu_button_hover;
    Surface menu_button_click;

    Surface retry_button_idle;
    Surface retry_button_hover;
    Surface retry_button_click;

    Surface pb_button_idle;
    Surface pb_button_hover;
    Surface pb_button_click;

    Surface htp_button_idle;
    Surface htp_button_hover;
    Surface htp_button_click;
    
    Surface pause_button_idle;
    Surface pause_button_hover;
    Surface pause_button_click;

    Surface option_button_idle;
    Surface option_button_hover;
    Surface option_button_click;
    
    Surface resume_button_idle;
    Surface resume_button_hover;
    Surface resume_button_click;

    Surface gameplay_background;
    Surface mainmenu_background;
    Surface credit_image;
    Surface game_frame;
    Surface instruction_image;
    Surface pb_background;
    Surface pause_background;
    Surface gameover_screen;

    Images();
    void load();
};

#endif