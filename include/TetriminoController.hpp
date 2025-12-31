#ifndef TETRIMINO_CONTROLLER_HPP
#define TETRIMINO_CONTROLLER_HPP
#include "engine/engine.hpp"
#include "Tetrimino.hpp"
#include "Sand.hpp"
#include "Game.hpp"
using Event = sdlgame::event::Event;
using Rect = sdlgame::rect::Rect;
using Vector2 = sdlgame::math::Vector2;
using Surface = sdlgame::surface::Surface;
using Color = sdlgame::color::Color;
using Sound = sdlgame::mixer::Sound;
using Channel = sdlgame::mixer::Channel;
using Font = sdlgame::font::Font;
using namespace std;


/**
 * 
 * The controller IS NOT RESPONSIBLE to check if the tetrimino is collide with any Sand yet,
 * that's the grid responsible for that
 * this also responsible for drawing and controlling the tetrimino movement, rotation
 * The grid should have a properties of type TetriminoController
*/
class TetriminoController
{
public:
    Surface draw_surf;
    Tetrimino tetrimino;
    Vector2 topleft;
    Game* game;
    TetriminoController(Game &game, Tetrimino tetrimino);
    TetriminoController();
    void reset(Tetrimino tetrimino);
    void draw();
    void redraw();
    void update();
    void rotate();
    void handle_event(Event &event);
};

#endif