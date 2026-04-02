#include "Sand.hpp"
#include "constant.hpp"

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
    mask = mask;
    color_offset_rgb = sdlgame::random::randint(0, 255);
    // inertia = 1;
}
