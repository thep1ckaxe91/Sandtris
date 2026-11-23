#pragma once
#ifndef TETRIS_CONSTANT_HPP
#define TETRIS_CONSTANT_HPP
#include <sdlgame/color.hpp>
#include <sdlgame/engine.hpp>
#include <sdlgame/math.hpp>
#include <sdlgame/rect.hpp>

using sdlgame::color::Color;
using sdlgame::math::Vector2;
using sdlgame::rect::Rect;

namespace sandtris::cfg {
enum WindowConstant { RESOLUTION_WIDTH = 160, RESOLUTION_HEIGHT = 144 };

constexpr auto MAXFPS = 10000;

enum GridDimension {
  GRID_WIDTH = 80,
  GRID_HEIGHT = 144 + 32 // the +32 is for the area tetrimino spawn, every
                         // update only apply to those in this range
};

constexpr int GRID_X = 16;
constexpr int GRID_Y = -32;

const int TETRIMINO_EDGE_SIZE = 32;

const int dx[] = {
    0,
    0,
    1,
    -1,
    // 1,-1,-1,1
};
const int dy[] = {
    1,
    -1,
    0,
    0,
    // 1,1,-1,-1
};

const int FONT_SIZE = 12;

const double fall_speed_pps = 40;
const double fast_fall_speed_pps = 80;
const double sideway_move_speed_pps = 100;
const int step_range = 3;
const Vector2 score_display_center = Vector2(132, 123);

const Color RED_SAND_COLOR = Color("crimson");
const Color GREEN_SAND_COLOR = Color("forest green");
const Color YELLOW_SAND_COLOR = Color("gold");
const Color BLUE_SAND_COLOR = Color("dodger blue");

const Vector2 spawn_pos = Vector2(40, -32);
const Rect next_shape_display_area = Rect(116, 25, 32, 31);
const Rect next_shape_display_rect = Rect(120, 28, 24, 24);
const Rect left_barrier = Rect(8, -32, 8, int(RESOLUTION_HEIGHT + 32));
const Rect right_barrier =
    Rect(16 + sandtris::cfg::GRID_WIDTH, -32, 8, int(RESOLUTION_HEIGHT + 32));
const Rect next_color_display_rect = Rect(129, 71, 7, 23);
const Rect count_down_display_rect = Rect(32, 51, 48, 16);

const Vector2 menu_button_pos = Vector2(39, 97);
const Vector2 retry_button_pos = Vector2(91, 97);
const Vector2 midbottom_newscore = Vector2(80, 42);
const Vector2 midbottom_pb = Vector2(80, 77);

const double gameplay_bg_speed = 10;

} // namespace sandtris::cfg

#endif
