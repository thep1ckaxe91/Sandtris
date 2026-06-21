#pragma once
#ifndef GRID_HPP
#define GRID_HPP
#include "Game.hpp"
#include "Sand.hpp"
#include "Tetrimino.hpp"
#include "TetriminoController.hpp"
#include "constant.hpp"
#include "memory.hpp"

/**
 * Yes, the array start from 1, the rest is the border
 */

class Grid {
private:
  double update_timer = 0; // erm, rather use struct

public:
  Surface ghost;
  Game &game;
  const double fixed_delta_time = 0.05;
  sdlgame::memory::SDLUniquePtr<SDL_Texture> sand_texture = nullptr;
  Vector2 ghost_topleft;
  TetriminoController controller;
  Color ghost_color;

  std::vector<std::pair<Uint8, Uint8>> pos;
  Tetrimino next;
  int score1 = 0, score2 = 0;

  std::array<std::array<Sand, GRID_WIDTH + 2>, GRID_HEIGHT + 2> grid{};

  Grid(Game &game);
  Grid(
      Game &game,
      const std::array<std::array<Sand, GRID_WIDTH + 2>, GRID_HEIGHT + 2> &grid,
      const Tetrimino &next, const TetriminoController &controller);

  // maybe we should still allow moving and copying? or just create a
  // constructor that allow restore state
  Grid(const Grid &) = delete;
  Grid(Grid &&) = delete;
  void operator=(const Grid &) = delete;
  void operator=(Grid &&) = delete;

  void normalize_tetrimino();

  void collision_check(std::vector<std::pair<Uint8, Uint8>> &updated);
  void merge(std::vector<std::pair<Uint8, Uint8>> &updated_sands);

  int get_score();
  int check_scoring(std::vector<std::pair<Uint8, Uint8>> &updated_sands);

  void update_ghost();
  void update_ghost_shape();
  void draw_ghost();

  void update();
  void draw();
  void handle_event(const Event &event);

  std::pair<Uint8, Uint8> step(int i, int j, int times);
};

#endif
