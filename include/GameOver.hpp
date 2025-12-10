#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "Scene.hpp"
#include "engine/engine.hpp"
#include "MenuButton.hpp"
#include "RetryButton.hpp"

class GameOver : public Scene
{
    MenuButton menu;
    RetryButton retry;
    Font score_font;
    Surface new_score_surf;
    Rect new_score_rect;
    Surface pb_surf;
    Rect pb_rect;
    int new_score;
    int pb;
public:
    GameOver(Game &game, int new_score);
    void handle_event(Event &event);
    void update();
    void draw();
};
#endif