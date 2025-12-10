#include "Sand.hpp"
#include "constant.hpp"
#include <map>
using namespace std;

//Bit shift for color check, not for actual color
map<SandShift,Color> SandShiftColor = {
    {EMPTY_SAND, Color()},
    {RED_SAND, RED_SAND_COLOR},
    {YELLOW_SAND, YELLOW_SAND_COLOR},
    {BLUE_SAND, BLUE_SAND_COLOR},
    {GREEN_SAND, GREEN_SAND_COLOR}
};
Sand::Sand(SandShift mask)
{
    this->mask = mask; 
    this->color_offset_rgb = sdlgame::random::randint(0,255);
    // this->inertia = 1;
}
