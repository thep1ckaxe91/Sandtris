#ifndef GRID_HPP
#define GRID_HPP
#include "Sand.hpp"
#include "constant.hpp"
#include "Tetrimino.hpp"
#include "tetriminoes.hpp"
#include "TetriminoController.hpp"
#include "Game.hpp"

/**
 * Yes, the array start from 1, the rest is the border
 */

class Grid
{
private:
    double update_timer = 0;

public:
    std::vector<std::pair<Uint8, Uint8>> pos;
    int score1 = 0, score2 = 0;
    Sand grid[GRID_HEIGHT + 2][GRID_WIDTH + 2];

    Tetrimino next;
    Surface ghost;
    Color ghost_color;
    Game *game;
    const double fixed_delta_time = 0.05;
    // this will be a life saver for drawing the grid
    SDL_Texture *sand_texture = nullptr;
    Vector2 ghost_topleft;
    TetriminoController controller;
    Grid(Game &game);
    Grid();
    ~Grid();
    Grid &operator=(const Grid &other);
    void collision_check(std::vector<std::pair<Uint8, Uint8>> &updated);
    void normalize_tetrimino();
    void merge(std::vector<std::pair<Uint8, Uint8>> &updated_sands);
    int get_score();
    int check_scoring(std::vector<std::pair<Uint8, Uint8>> &updated_sands);
    void handle_event(Event &event);
    void update_ghost();
    void update_ghost_shape();
    void draw_ghost();
    void update();
    void draw();

    // these function should make the sand fall better somehow

    std::pair<Uint8, Uint8> step(int i, int j, int times);
};

#endif