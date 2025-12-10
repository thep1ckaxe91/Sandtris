#ifndef HOW_TO_PLAY_HPP
#define HOW_TO_PLAY_HPP

#include "Scene.hpp"
#include "BackButton.hpp"
#include "Game.hpp"
class HowToPlay : public Scene
{
public:
    BackButton back_button;
    double height_pos;
    const Vector2 bb_pos = Vector2(123,123);
    HowToPlay(Game &game);
    void handle_event(Event &event);
    void update();
    void draw();
};


#endif