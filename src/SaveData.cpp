#include "SaveData.hpp"
#include "Game.hpp"
#include "Grid.hpp"
#include "constant.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

namespace fs = std::filesystem;

int bytes_to_int(const char *c) {
  int val;
  memcpy(&val, c, 4);
  return val;
}

char *int_to_bytes(int x) {
  char *res = new char[4];
  memcpy(res, &x, 4);
  return res;
}

double bytes_to_double(const char *c) {
  double val;
  memcpy(&val, c, 8);
  return val;
}

char *double_to_bytes(double x) {
  char *res = new char[8];
  memcpy(res, &x, 8);
  return res;
}

int get_personal_best() {
  return 0; // Stub for now
}

void set_personal_best(int score) {
  // Stub for now
}

float get_sfx_volume() {
  if (!fs::exists(base_path / "assets" / "save" / "sfx_volume.sandtris")) {
    set_sfx_volume(1.0f);
    return 1.0f;
  }
  std::ifstream file{base_path / "assets" / "save" / "sfx_volume.sandtris"};
  float res = 1.0f;
  try {
    file >> res;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return res;
}

float get_music_volume() {
  if (!fs::exists(base_path / "assets" / "save" / "music_volume.sandtris")) {
    set_music_volume(1.0f);
    return 1.0f;
  }
  std::ifstream file{base_path / "assets" / "save" / "music_volume.sandtris"};
  float res = 1.0f;
  try {
    file >> res;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return res;
}

void set_sfx_volume(float value) {
  std::ofstream file(base_path / "assets" / "save" / "sfx_volume.sandtris");
  file << (value < 0 ? 0 : (value > 1 ? 1 : value));
}

void set_music_volume(float value) {
  std::ofstream file(base_path / "assets" / "save" / "music_volume.sandtris");
  file << (value < 0 ? 0 : (value > 1 ? 1 : value));
}

bool have_grid_data() {
  return fs::exists(base_path / "assets" / "save" / "grid.sandtris");
}

bool delete_grid_data() {
  try {
    return fs::remove(base_path / "assets" / "save" / "grid.sandtris");
  } catch (const fs::filesystem_error &e) {
    std::cerr << "Error deleting file: " << e.what() << std::endl;
    return false;
  }
}

bool save_grid_data(Grid &grid) {
  return false; // Stub for now
}

void load_grid_data(Game &game, Grid &grid) {
  std::ifstream file(base_path / "assets" / "save" / "grid.sandtris",
                     std::ios_base::binary);
  if (!file.is_open()) return;

  char tmp[8];
  uint8_t tmp_byte;
  uint8_t tmp_byte2;

  file.read(tmp, 8);
  grid.controller.topleft.x = bytes_to_double(tmp);
  file.read(tmp, 8);
  grid.controller.topleft.y = bytes_to_double(tmp);

  file.read((char *)&tmp_byte, 1);  // color
  file.read((char *)&tmp_byte2, 1); // type
  Tetrimino cur_tetrimino((char)tmp_byte2, (SandShift)tmp_byte);
  grid.controller.tetrimino = cur_tetrimino;

  file.read((char *)&tmp_byte, 1);
  grid.controller.tetrimino.current_rotation = tmp_byte;
  grid.controller.redraw();

  file.read((char *)&tmp_byte, 1);  // type
  file.read((char *)&tmp_byte2, 1); // color
  Tetrimino next_t(char(tmp_byte), (SandShift)tmp_byte2);
  grid.next = next_t;

  file.read(tmp, 4);
  int total_score = bytes_to_int(tmp);
  if (total_score != 0) {
    grid.score2 = total_score / 2;
    grid.score1 = total_score - grid.score2;
  }

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      file.read((char *)&tmp_byte, 1);
      grid.grid[i + 1][j + 1].mask = SandShift(tmp_byte);
    }
  }
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      file.read((char *)&tmp_byte, 1);
      grid.grid[i + 1][j + 1].color_offset_rgb = tmp_byte;
    }
  }
}

bool save_window_info(int x, int y, int width, int height) {
  std::ofstream file(base_path / "assets" / "save" / "resolution.sandtris");
  try {
    file << x << " " << y << " " << width << " " << height;
  } catch (const std::exception &e) {
    std::cerr << "Cant save info" << std::endl;
    return false;
  }
  if (file.bad() or file.fail()) {
    return false;
  }
  return true;
}

std::pair<std::pair<int, int>, std::pair<int, int>> load_window_info() {
  std::pair<std::pair<int, int>, std::pair<int, int>> res = {{0, 0}, {0, 0}};
  try {
    std::ifstream file(base_path / "assets" / "save" / "resolution.sandtris");
    if (file.is_open()) {
      file >> res.first.first >> res.first.second >> res.second.first >>
          res.second.second;
      if (res.second.first == 0 or res.second.second == 0)
        return {{0, 0}, {0, 0}};
    }
  } catch (const std::exception &e) {
    std::cerr << "Cant load info\n" << std::endl;
    return {{0, 0}, {0, 0}};
  }
  return res;
}
