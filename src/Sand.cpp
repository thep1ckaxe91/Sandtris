#include "Sand.hpp"
#include "constant.hpp"
#include <map>

// Bit shift for color check, not for actual color, does not include static_sand
std::array<Color, 9> SandShiftColor = {
    Color(),
    RED_SAND_COLOR,
    YELLOW_SAND_COLOR,
    Color(),
    BLUE_SAND_COLOR,
    Color(),
    Color(),
    Color(),
    GREEN_SAND_COLOR};
Sand::Sand(SandShift mask)
{
    this->mask = mask;
    this->color_offset_rgb = sdlgame::random::randint(0, 255);
    // this->inertia = 1;
}
