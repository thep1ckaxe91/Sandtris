#ifndef GRID_HPP
#define GRID_HPP
#include "Game.hpp"
#include "Sand.hpp"
#include "Tetrimino.hpp"
#include "TetriminoController.hpp"
#include "constant.hpp"
#include "memory.hpp"
#include "tetriminoes.hpp"

/**
 * Yes, the array start from 1, the rest is the border
 */

class Grid {
private:
  double update_timer = 0;

public:
  Surface ghost;
  Game &game;
  const double fixed_delta_time = 0.05;
  sdlgame::memory::SDLUniquePtr<SDL_Texture> sand_texture = nullptr;
  Vector2 ghost_topleft;
  TetriminoController controller;
  std::vector<std::pair<Uint8, Uint8>> pos;
  int score1 = 0, score2 = 0;
  Tetrimino next;

  Color ghost_color;

  Sand grid[GRID_HEIGHT + 2][GRID_WIDTH + 2];

  Grid(Game &game);
  Grid(const Grid &) = delete;
  Grid(Grid &&) = delete;
  void operator=(const Grid &) = delete;
  void operator=(Grid&&) = delete;

  void collision_check(std::vector<std::pair<Uint8, Uint8>> &updated);
  void normalize_tetrimino();
  void merge(std::vector<std::pair<Uint8, Uint8>> &updated_sands);
  int get_score();
  int check_scoring(std::vector<std::pair<Uint8, Uint8>> &updated_sands);
  void handle_event(const Event &event);
  void update_ghost();
  void update_ghost_shape();
  void draw_ghost();
  void update();
  void draw();

  // these function should make the sand fall better somehow

  std::pair<Uint8, Uint8> step(int i, int j, int times);
};

#endif