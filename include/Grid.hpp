#pragma once
#ifndef GRID_HPP
#define GRID_HPP
#include "Game.hpp"
#include "Sand.hpp"
#include "Tetrimino.hpp"
#include "TetriminoController.hpp"
#include "constant.hpp"
#include <sdlgame/surface.hpp>

/**
 * Yes, the array start from 1, the rest is the border
 */

struct GridPos {
  std::uint8_t row;
  std::uint8_t col;

  GridPos(std::uint8_t _row, std::uint8_t _col) : row(_row), col(_col) {}
  constexpr bool operator==(const GridPos &) const = default;
};

class Grid {
private:
  double update_timer = 0; // erm, rather use struct
public:
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_TARGET> ghost;
  Game &game;
  const double fixed_delta_time = 0.05;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STREAMING> sand_texture;
  sdlgame::math::Vector2 ghost_topleft;
  TetriminoController controller;
  sdlgame::color::Color ghost_color;

  std::vector<GridPos> score_cells;
  Tetrimino next;
  int score1 = 0, score2 = 0;

  std::array<std::array<Sand, GRID_WIDTH + 2>, GRID_HEIGHT + 2> grid{};

  Grid(Game &game);
  Grid(
      Game &game,
      const std::array<std::array<Sand, GRID_WIDTH + 2>, GRID_HEIGHT + 2> &grid,
      const Tetrimino &next, const TetriminoController &controller);

  // TODO: maybe we should still allow moving and copying? or just create a
  // constructor that allow restore state
  Grid(const Grid &) = delete;
  Grid(Grid &&) = delete;
  void operator=(const Grid &) = delete;
  void operator=(Grid &&) = delete;

  void normalize_tetrimino();

  void collision_check(std::vector<GridPos> &updated);
  void merge(std::vector<GridPos> &updated_sands);

  int get_score();
  int check_scoring(std::vector<GridPos> &updated_sands);

  void update_ghost();
  void update_ghost_shape();
  void draw_ghost();

  void update();
  void draw();
  void handle_event(const sdlgame::event::Event &event);

  GridPos step(GridPos, int);
};

#endif
