#ifndef SAVEDATA_HPP
#define SAVEDATA_HPP
#include "constant.hpp"
#include "Grid.hpp"
using namespace std;

int get_personal_best();
void set_personal_best(int score);

int bytes_to_int(const char *c);
char *int_to_bytes(int x);

float get_sfx_volume();
float get_music_volume();
void set_sfx_volume(float value);
void set_music_volume(float value);
// check if there's on going Gameplay
bool have_grid_data();
bool delete_grid_data();
bool save_grid_data(Grid &grid);
Grid load_grid_data(Game *game);

bool save_window_info(int x,int y, int width, int height);
pair<pair<int,int>,pair<int,int>> load_window_info();

#endif