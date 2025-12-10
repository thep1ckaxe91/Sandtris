#ifndef CREDIT_HPP
#define CREDIT_HPP

#include "Scene.hpp"
#include "BackButton.hpp"
#include "Game.hpp"
class Credit : public Scene
{
public:
    BackButton back_button;
    const Vector2 bb_pos = Vector2(123,123);
    Credit(Game &game);
    void handle_event(Event &event);
    void update();
    void draw();
};


#endif