#ifndef PERSONAL_BEST_HPP
#define PERSONAL_BEST_HPP

#include "Scene.hpp"
#include "Game.hpp"
#include "BackButton.hpp"
class PersonalBest : public Scene
{
public:
    Font pb_font;
    Surface pb_surf;
    Rect pb_rect;
    const Vector2 pb_center = Vector2(81,79);
    int score;
    BackButton back_button;
    const Vector2 bb_pos = Vector2(66,103);
    PersonalBest(Game &game);
    void update();
    void draw();
    void handle_event(Event &event);
};

#endif