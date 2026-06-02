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
Sand::Sand(SandShift mask_val) : mask(mask_val), color_offset_rgb(static_cast<Uint8>(sdlgame::random::randint(0, 255))){}
