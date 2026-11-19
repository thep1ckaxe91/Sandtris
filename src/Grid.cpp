#include "Grid.hpp"
#include "TetriminoController.hpp"
#include "TetrisEvent.hpp"
#include "constant.hpp"
#include "tetriminoes.hpp"
#include <SDL_render.h>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <queue>
#include <sdlgame/color.hpp>
#include <sdlgame/draw.hpp>
#include <sdlgame/math.hpp>
#include <sdlgame/random.hpp>
#include <sdlgame/rect.hpp>
#include <sdlgame/surface.hpp>

template <SDL_TextureAccess Ac> using Surface = sdlgame::surface::Surface<Ac>;
using sdlgame::color::Color;
using sdlgame::math::Vector2;
using sdlgame::rect::Rect;
using sdlgame::surface::BlendMode;
using namespace std::string_literals;

Grid::Grid(Game &game_ref)
    : ghost(Surface<SDL_TEXTUREACCESS_TARGET>(32, 32)), game(game_ref),
      sand_texture(GRID_WIDTH, GRID_HEIGHT), ghost_topleft(0, -1000),
      controller(TetriminoController(game_ref, Tetriminoes::randomTetrimino())),
      ghost_color("white"s), next(Tetriminoes::randomTetrimino()) {
  update_ghost_shape();

  for (int row = 0; row < GRID_HEIGHT + 2; row++)
    grid[row][0] = grid[row][GRID_WIDTH + 1] = Sand(SandShift::STATIC_SAND);
  for (int col = 0; col < GRID_WIDTH + 2; col++)
    grid[0][col] = grid[GRID_HEIGHT + 1][col] = Sand(SandShift::STATIC_SAND);

  sand_texture.set_blendmode(BlendMode::NONE);
}

void Grid::handle_event(const sdlgame::event::Event &event) {
  controller.handle_event(event);
  if (event.type == sdlgame::KEYDOWN) {
    if (event["key"] == sdlgame::K_SPACE) {
      sdlgame::event::post(SLAM);
      // move the tetrimino to the lowest point right below and immediatly merge
      controller.topleft = ghost_topleft;
    } else if (event["key"] == sdlgame::K_p) {
      sdlgame::event::post(GAME_PAUSE);
      // pause scene
    } else if (event["key"] == sdlgame::K_w or event["key"] == sdlgame::K_UP) {
      update_ghost_shape();
    }
  }
}
void Grid::normalize_tetrimino() {
  // when rotate, it possible to collide with edge, in that case, we should
  // shift the position of the tetrimino
  for (int shift = 0; shift < 16; shift++) {
    if (controller.tetrimino.mask >> shift & 1) {
      Rect tmp = Rect(controller.topleft +
                          Vector2((3 - shift % 4) * 8,
                                  (3 - static_cast<int>(shift / 4)) * 8),
                      8, 8);
      for (int i = 0; i < 2; i++) {
        if (tmp.colliderect(left_barrier)) {
          // printf("collide left\n");
          tmp.setLeft(left_barrier.getRight());
          controller.topleft.x = tmp.getLeft() - (3 - shift % 4) * 8;
        }
      }
      for (int i = 0; i < 2; i++) {
        if (tmp.colliderect(right_barrier)) {
          // printf("collide right\n");
          tmp.setRight(right_barrier.getLeft());
          controller.topleft.x = tmp.getLeft() - (3 - shift % 4) * 8;
        }
      }
    }
  }
}
int Grid::get_score() { return score1 + score2; }

/**
 * @brief check if is scoring anything
 *
 * @param updated_sands a list of position sand that got updated
 * @return an integer represent amount of point we get
 */
int Grid::check_scoring(std::vector<GridPos> &updated_sands) {
  std::queue<GridPos> q;
  score_cells.clear();
  std::array<std::bitset<GRID_WIDTH + 2>, GRID_HEIGHT + 2> visited;
  for (auto &[row, col] : updated_sands) {
    if (visited[row][col] == 1)
      continue;
    visited[row][col] = 1;
    std::vector<GridPos> tmp;
    SandShift check_color = grid[row][col].mask;
    bool touchleft = 0, touchright = 0;
    q.push({row, col});
    while (!q.empty()) {
      GridPos u = q.front();
      tmp.push_back(u);
      q.pop();
      if (u.col == 1)
        touchleft = 1;
      else if (u.col == GRID_WIDTH)
        touchright = 1;
      for (size_t k = 0; k < (sizeof(dx) / sizeof(int)); k++) {
        int x = dx[k] + u.row;
        int y = dy[k] + u.col;

        if (visited[x][y] == 0 and grid[x][y].mask == check_color) {
          q.push({static_cast<uint8_t>(x), static_cast<uint8_t>(y)});
          visited[x][y] = 1;
        }
      }
    }
    if (touchleft and touchright) {
      for (GridPos v : tmp) {
        score_cells.push_back(v);
      }
    }
  }
  if (score_cells.size() > 0) {
    for (auto &[i, j] : score_cells) {
      grid[i][j] = Sand();
    }
    sdlgame::event::post(SCORING);
  }
  return static_cast<int>(score_cells.size());
}

static std::pair<int, int> shift_to_xy(int shift) {
  return {3 - shift % 4, 3 - shift / 4};
}

void Grid::merge(std::vector<GridPos> &updated) {
  // if merge at wrong place, game over
  // a bit offset for more comfort ux
  game.m_window_draw_offset.y = 2;
  if (controller.topleft.y + 7 < 0) {
    sdlgame::event::post(GAMEOVER);
    game.m_window_draw_offset.y = 0;
    return;
  }
  // merge
  for (int shift = 0; shift < 16; shift++) {
    if (controller.tetrimino.mask >> shift & 1) {
      auto [x, y] = shift_to_xy(shift);
      int start_x = x * 8 + static_cast<int>(controller.topleft.x) - GRID_X + 1;
      int start_y = y * 8 + static_cast<int>(controller.topleft.y) - GRID_Y + 1;

      for (int i = start_y; i < start_y + 8; i++) {
        for (int j = start_x; j < start_x + 8; j++) {
          if (i >= 1 && i <= GRID_HEIGHT && j >= 1 && j <= GRID_WIDTH) {
            updated.push_back(
                {static_cast<uint8_t>(i), static_cast<uint8_t>(j)});
            grid[i][j].mask = controller.tetrimino.color;
          }
        }
      }
    }
  }
}
void Grid::collision_check(std::vector<GridPos> &updated) {
  for (int i = 1; i <= GRID_HEIGHT + 1; i++) {
    for (int j = 1; j <= GRID_WIDTH; j++) {
      if (grid[i][j].mask != SandShift::EMPTY_SAND) {
        for (int shift = 0; shift < 16; shift++) {
          if (controller.tetrimino.mask >> shift & 1) {
            auto [x, y] = shift_to_xy(shift);
            Rect tmp = Rect(controller.topleft + Vector2(x * 8, y * 8), 8, 8);
            if (tmp.collidepoint(j + GRID_X, i + GRID_Y - 1)) {
              Vector2 check_point(j + GRID_X, i + GRID_Y);
              while (tmp.collidepoint(check_point)) {
                controller.topleft.y -= 1;
                tmp.move_ip(0, -1);
                int check_y = int(check_point.y - GRID_Y - 1);
                int check_x = int(check_point.x - GRID_X);
                if (check_y >= 0 && check_y < GRID_HEIGHT + 2 && check_x >= 0 &&
                    check_x < GRID_WIDTH + 2) {
                  if (grid[check_y][check_x].mask != SandShift::EMPTY_SAND)
                    check_point.y--;
                }
              }
              merge(updated);
              controller.reset(next);
              next = Tetriminoes::randomTetrimino();
              sdlgame::event::post(MERGING);
              update_ghost_shape();
              return;
            }
          }
        }
      }
    }
  }
}

GridPos Grid::step(GridPos pos, int times) {
  int x = pos.row, y = pos.col;
  while (times--) {
    auto left = grid[x + 1][y - 1].mask != 0;
    auto mid = grid[x + 1][y].mask != 0;
    auto right = grid[x + 1][y + 1].mask != 0;
    int d_row = !(left && mid && right);
    int d_col = mid * (left - right);
    x += d_row;
    y += d_col;
  }
  std::swap(grid[pos.row][pos.col], grid[x][y]);
  return {static_cast<uint8_t>(x), static_cast<uint8_t>(y)};
}

void Grid::update_ghost_shape() {
  auto get_from_pos = [&](const int i, const int j) {
    return (3 - i) * 4 + (3 - j);
  };
  ghost.fill(Color{"none"});
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (controller.tetrimino.mask >> get_from_pos(i, j) & 1) {
        sdlgame::draw::rect(ghost, ghost_color, Rect(j * 8, i * 8, 8, 8), 1);
      }
    }
  }
}

void Grid::update_ghost() {
  std::bitset<4> checked;      // if the i-th column is checked or not
  int min_drop_distance = 144; // min vertical distance the ghost can fall

  const int controller_x = static_cast<int>(controller.topleft.x),
            controller_y = static_cast<int>(controller.topleft.y);

  for (int shift = 0; shift < 16; shift++) {
    if ((controller.tetrimino.mask >> shift & 1) && !checked[shift % 4]) {
      checked[shift % 4] = 1;
      const auto [x, y] = shift_to_xy(shift);
      const int left = static_cast<int>(controller_x) + 8 * x - GRID_X;
      const int right = left + 8;

      for (int j = left; j < right; j++) {
        int i = controller_y + 8 * y - GRID_Y;
        int cnt = 0;
        while (i < GRID_HEIGHT + 1 &&
               grid[i++][j + 1].mask == SandShift::EMPTY_SAND) {
          if (++cnt >= min_drop_distance)
            break;
        }
        min_drop_distance = std::min(min_drop_distance, cnt);
      }
    }
  }

  ghost_topleft =
      Vector2(controller_x, controller_y + min_drop_distance - 8 - 1);
}
void Grid::update() {
  update_timer += game.m_clock.delta_time().count();
  if (update_timer >= fixed_delta_time) {
    std::vector<GridPos> updated_sands;
    update_timer -= fixed_delta_time;

    for (int row = GRID_HEIGHT; row >= 1; row--) {
      for (int col = 1; col <= GRID_WIDTH; col++) {
        if (grid[row][col].mask != SandShift::EMPTY_SAND) {
          int step_times = sdlgame::random::randint(1, step_range);
          GridPos new_pos =
              step({static_cast<uint8_t>(row), static_cast<uint8_t>(col)},
                   step_times);
          if (row != new_pos.row || col != new_pos.col)
            updated_sands.push_back(new_pos);
        }
      }
    }
    collision_check(updated_sands);
    if (!updated_sands.empty()) {
      int added = check_scoring(updated_sands);
      if (added > 0) {
        int split = sdlgame::random::randint(2, added - 2);
        score1 += split;
        score2 += added - split;
      }
    }
  }
  if (game.m_window_draw_offset.y != 0)
    game.m_window_draw_offset.y--;
  controller.update();
  normalize_tetrimino();
  update_ghost();
}
void Grid::draw_ghost() { game.m_window.blit(ghost, ghost_topleft); }
void Grid::draw() {

  sand_texture.lock();

  auto [raw_pixels, pitch] = sand_texture.get_lock();

  auto *pixels = reinterpret_cast<uint32_t *>(raw_pixels);
  int width_in_pixels = pitch / 4;

  for (int row = 1; row <= GRID_HEIGHT; row++) {
    int row_offset = (row - 1) * width_in_pixels;
    for (int col = 1; col <= GRID_WIDTH; col++) {
      if (grid[row][col].mask == SandShift::EMPTY_SAND) {
        pixels[row_offset + (col - 1)] = 0xff000000;
        continue;
      }
      Color c = SandShiftColor.at(static_cast<uint8_t>(grid[row][col].mask)) +
                Color{uint8_t(grid[row][col].color_offset_rgb >> 4 & 15),
                      uint8_t(grid[row][col].color_offset_rgb >> 2 & 15),
                      uint8_t(grid[row][col].color_offset_rgb & 15)};

      uint32_t pixel_color = (255 << 24) | (c.r << 16) | (c.g << 8) | c.b;
      pixels[row_offset + (col - 1)] = pixel_color;
    }
  }

  sand_texture.unlock();

  game.m_window.blit(sand_texture, {GRID_X, GRID_Y});

  controller.draw();
  draw_ghost();
}
