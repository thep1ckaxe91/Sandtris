#pragma once
#ifndef TETRIMINO_CONTROLLER_HPP
#define TETRIMINO_CONTROLLER_HPP
#include "Game.hpp"
#include "Tetrimino.hpp"
/**
 *
 * The controller IS NOT RESPONSIBLE to check if the tetrimino is collide with
 * any Sand yet, that's the grid responsible for that this also responsible for
 * drawing and controlling the tetrimino movement, rotation The grid should have
 * a properties of type TetriminoController
 */
class TetriminoController {
public:
  Game &game;
  Tetrimino tetrimino;
  Surface draw_surf;
  Vector2 topleft;
  TetriminoController(Game &game, Tetrimino tetrimino);
  
  // deleted default constructor because of Game&
  TetriminoController() = delete;
  
  void reset(Tetrimino tetrimino);
  void draw();
  void redraw();
  void update();
  void rotate();
  void handle_event(const Event &event);
};

#endif
