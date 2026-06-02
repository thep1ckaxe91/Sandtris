#include "Grid.hpp"
#include "TetriminoController.hpp"
#include "TetrisEvent.hpp"
#include "constant.hpp"
#include "engine.hpp"
#include "tetriminoes.hpp"
#include <bitset>
#include <queue>

using namespace std::string_literals;

Grid::Grid(Game &game_ref)
    : ghost(Surface(32, 32)), game(game_ref),
      ghost_topleft(0, -1000), controller(TetriminoController(game_ref, Tetriminoes::randomTetrimino())),
      ghost_color("white"s), next(Tetriminoes::randomTetrimino()) {
  update_ghost_shape();

  for (int i = 0; i < GRID_HEIGHT + 2; i++)
    grid[i][0] = grid[i][GRID_WIDTH + 1] = Sand(SandShift::STATIC_SAND);
  for (int i = 0; i < GRID_WIDTH + 2; i++)
    grid[0][i] = grid[GRID_HEIGHT + 1][i] = Sand(SandShift::STATIC_SAND);
  for (int i = 1; i <= GRID_HEIGHT; i++)
    for (int j = 1; j <= GRID_WIDTH; j++)
      grid[i][j] = Sand();

  sand_texture.reset(SDL_CreateTexture(
      sdlgame::display::get_renderer(), SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING, // cpu can write to this tex
      GRID_WIDTH, GRID_HEIGHT));

  if (!sand_texture) {
    SDL_Log("Cant create or sand texture null for:\n%s\n", SDL_GetError());
    exit(1);
  }
  if (SDL_SetTextureBlendMode(sand_texture.get(), SDL_BLENDMODE_NONE)) {
    SDL_Log("Failed to set texture blend mode due to: %s", SDL_GetError());
  }
}

void Grid::handle_event(const Event &event) {
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
int Grid::check_scoring(
    std::vector<std::pair<uint8_t, uint8_t>> &updated_sands) {
  std::queue<std::pair<uint8_t, uint8_t>> q;
  pos.clear();
  std::array<std::bitset<GRID_WIDTH + 2>, GRID_HEIGHT + 2> visited;
  for (auto &[i, j] : updated_sands) {
    if (visited[i][j] == 1)
      continue;
    visited[i][j] = 1;
    std::vector<std::pair<uint8_t, uint8_t>> tmp;
    SandShift check_color = grid[i][j].mask;
    bool touchleft = 0, touchright = 0;
    q.push({i, j});
    while (!q.empty()) {
      auto u = q.front();
      tmp.push_back(u);
      q.pop();
      if (u.second == 1)
        touchleft = 1;
      else if (u.second == GRID_WIDTH)
        touchright = 1;
      for (size_t k = 0; k < (sizeof(dx) / sizeof(int)); k++) {
        int x = dx[k] + u.first;
        int y = dy[k] + u.second;
        if (visited[x][y] == 0 and grid[x][y].mask == check_color) {
          q.push({x, y});
          visited[x][y] = 1;
        }
      }
    }
    if (touchleft and touchright) {
      for (auto &v : tmp)
        pos.push_back(v);
    }
  }
  if (pos.size() > 0) {
    for (auto &[i, j] : pos) {
      grid[i][j] = Sand();
    }
    sdlgame::event::post(SCORING);
  }
  return static_cast<int>(pos.size());
}

static std::pair<int, int> shift_to_xy(int shift) {
  return {3 - shift % 4, 3 - shift / 4};
}

void Grid::merge(std::vector<std::pair<uint8_t, uint8_t>> &updated) {
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
            updated.push_back({i, j});
            grid[i][j].mask = controller.tetrimino.color;
          }
        }
      }
    }
  }
}
void Grid::collision_check(std::vector<std::pair<uint8_t, uint8_t>> &updated) {
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
                if (check_y >= 0 && check_y < GRID_HEIGHT + 2 && check_x >= 0 && check_x < GRID_WIDTH + 2) {
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

std::pair<uint8_t, uint8_t> Grid::step(int i, int j, int times) {
  int x = i, y = j;
  while (times--) {
    x += ((grid[i + 1][j - 1].mask | grid[i + 1][j].mask |
           grid[i + 1][j + 1].mask) != 0);

    y += (grid[i + 1][j].mask != 0) *
         ((grid[i + 1][j + 1].mask != 0) - (grid[i + 1][j - 1].mask != 0));
  }
  if (i != x || j != y) {
    std::swap(grid[i][j], grid[x][y]);
  }
  return {x, y};
}

void Grid::update_ghost_shape() {
  auto get_from_pos = [&](const int i, const int j) {
    return (3 - i) * 4 + (3 - j);
  };
  ghost.fill("none"s);
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
        while (i < GRID_HEIGHT + 1 && grid[i++][j + 1].mask == SandShift::EMPTY_SAND) {
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
    std::vector<std::pair<uint8_t, uint8_t>> updated_sands;
    update_timer -= fixed_delta_time;

    for (int i = GRID_HEIGHT; i >= 1; i--) {
      for (int j = 1; j <= GRID_WIDTH; j++) {
        if (grid[i][j].mask != SandShift::EMPTY_SAND) {
          int step_times = sdlgame::random::randint(1, step_range);
          std::pair<uint8_t, uint8_t> new_pos = step(i, j, step_times);
          if (i != new_pos.first or j != new_pos.second)
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
void Grid::draw_ghost() {
  game.m_window.blit(ghost, ghost_topleft);
}
void Grid::draw() {
  void *raw_pixels;
  int pitch;

  if (SDL_LockTexture(sand_texture.get(), nullptr, &raw_pixels, &pitch)) {
    SDL_Log("Cant get memory address of sand texture:\n%s\n", SDL_GetError());
    exit(1);
  }

  auto *pixels = reinterpret_cast<uint32_t *>(raw_pixels);
  int width_in_pixels = pitch / 4;

  for (int i = 1; i <= GRID_HEIGHT; i++) {
    int row_offset = (i - 1) * width_in_pixels;
    for (int j = 1; j <= GRID_WIDTH; j++) {
      if (grid[i][j].mask == SandShift::EMPTY_SAND) {
        pixels[row_offset + (j - 1)] = 0xff000000;
        continue;
      }
      Color c = SandShiftColor.at(static_cast<uint8_t>(grid[i][j].mask)) + Color{uint8_t(grid[i][j].color_offset_rgb >> 4 & 15),
                 uint8_t(grid[i][j].color_offset_rgb >> 2 & 15),
                 uint8_t(grid[i][j].color_offset_rgb & 15)};

      uint32_t pixel_color = (255 << 24) | (c.r << 16) | (c.g << 8) | c.b;
      pixels[row_offset + (j - 1)] = pixel_color;
    }
  }

  SDL_UnlockTexture(sand_texture.get());

  SDL_Rect dst_rect = {GRID_X, GRID_Y, GRID_WIDTH, GRID_HEIGHT};

  SDL_SetRenderTarget(sdlgame::display::get_renderer(),
                      game.m_window.getTexture());
  if (SDL_RenderCopy(sdlgame::display::get_renderer(), sand_texture.get(),
                     nullptr, &dst_rect)) {
    printf("Failed to render the sand texture:\n%s\n", SDL_GetError());
    exit(1);
  }
  SDL_SetRenderTarget(sdlgame::display::get_renderer(), nullptr);

  controller.draw();
  draw_ghost();
}
