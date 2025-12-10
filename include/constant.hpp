#ifndef TETRIS_CONSTANT_HPP
#define TETRIS_CONSTANT_HPP
#include "engine/engine.hpp"
const std::string base_path = sdlgame::get_base_path();
typedef enum
{
    RESOLUTION_WIDTH = 160,
    RESOLUTION_HEIGHT = 144
} Window_Constant;
const int MAXFPS = 60;
typedef enum
{
    GRID_WIDTH = 80,
    GRID_HEIGHT = 144 + 32 // the +32 is for the area tetrimino spawn, every update only apply to those in this range
} grid_size;
typedef enum
{
    GRID_X = 16,
    GRID_Y = -32,
} grid_pos;
typedef enum
{
    EDGE_SIZE = 32,
} tetrimino_size;
typedef enum
{
    NONE = 0,
    ADD = 1,
    POP = 2,
    REMOVE = 3,
    CLEAR = 4,
} SceneCommand;
const int dx[] =
{
    0, 0, 1, -1,
    // 1,-1,-1,1
};
const int dy[] =
{
    1, -1, 0, 0,
    // 1,1,-1,-1
};
typedef enum
{
    EMPTY_SAND = 0x0,   // 0000 0000
    RED_SAND = 0x1,     // 0000 0001
    YELLOW_SAND = 0x2,  // 0000 0010
    BLUE_SAND = 0x4,    // 0000 0100
    GREEN_SAND = 0x8,   // 0000 1000
    STATIC_SAND = 0x80, // 1000 0000
} SandShift;

const int FONT_SIZE = 10;

const double fall_speed = 40;          // pixel per second
const double fast_fall_speed = 80;     // pps
const double sideway_move_speed = 100; // pps
const int step_range = 3;
const Vector2 score_display_center = Vector2(132, 123);

const Color RED_SAND_COLOR = Color("crimson");
const Color GREEN_SAND_COLOR = Color("forest green");
const Color YELLOW_SAND_COLOR = Color("gold");
const Color BLUE_SAND_COLOR = Color("dodger blue");

const sdlgame::math::Vector2 spawn_pos = sdlgame::math::Vector2(40, -32);
const Rect next_shape_display_area = Rect(116, 25, 32, 31);
const Rect next_shape_display_rect = Rect(120, 28, 24, 24);
const Rect left_barrier = Rect(8, -32, 8, int(RESOLUTION_HEIGHT+32));
const Rect right_barrier = Rect(16 + GRID_WIDTH, -32, 8, int(RESOLUTION_HEIGHT+32));
const Rect next_color_display_rect = Rect(129, 71, 7, 23);
const Rect count_down_display_rect = Rect(32,51,48,16);

const Vector2 menu_button_pos = Vector2(39,97);
const Vector2 retry_button_pos = Vector2(91,97);
const Vector2 midbottom_newscore = Vector2(80,42);
const Vector2 midbottom_pb = Vector2(80,77);

const double gameplay_bg_speed = 10;
const double gforce = 1; //pix/sec^2
const int client_cores = std::thread::hardware_concurrency();
const std::string font_path = base_path + "data\\fonts\\sandtris pixel.ttf";
#endif