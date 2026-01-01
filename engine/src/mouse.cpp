#include "mouse.hpp"
#include "display.hpp"
#include "SDL2/SDL_mouse.h"
#include "math.hpp"
#include <vector>
sdlgame::math::Vector2 sdlgame::mouse::last_mouse_pos;
bool sdlgame::mouse::isVisible;
sdlgame::math::Vector2 sdlgame::mouse::get_pos()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    double reso_ratio = sdlgame::display::resolution.x / sdlgame::display::resolution.y;
    double win_ratio = sdlgame::display::win_surf.size.x / sdlgame::display::win_surf.size.y;
    sdlgame::math::Vector2 offset(
        (win_ratio>reso_ratio)*(sdlgame::display::win_surf.size.x-sdlgame::display::win_surf.size.y*reso_ratio)/2,
        (win_ratio<reso_ratio)*(sdlgame::display::win_surf.size.y-sdlgame::display::win_surf.size.x/reso_ratio)/2
    );
    //how much did the window grow 
    double scale = (win_ratio > reso_ratio ? sdlgame::display::win_surf.size.y / sdlgame::display::resolution.y : sdlgame::display::win_surf.size.x / sdlgame::display::resolution.x);
    return (sdlgame::math::Vector2(x,y) - offset) * (1/scale);
}
std::vector<bool> sdlgame::mouse::get_pressed()
{
    int numButtons = 32;
    Uint32 buttonState = SDL_GetMouseState(NULL, NULL);

    std::vector<bool> buttons(numButtons);
    for (int i = 0; i < numButtons; ++i)
    {
        buttons[i] = buttonState & (1 << i);
    }
    return buttons;
}
sdlgame::math::Vector2 sdlgame::mouse::get_rel()
{
    if (last_mouse_pos == sdlgame::math::Vector2(-1, -1))
        return sdlgame::math::Vector2(0, 0);
    int x, y;
    SDL_GetMouseState(&x, &y);
    sdlgame::math::Vector2 res = sdlgame::math::Vector2(x, y) - last_mouse_pos;
    last_mouse_pos = sdlgame::math::Vector2(x, y);
    return res;
}
void sdlgame::mouse::set_visible(int enable)
{
    isVisible = SDL_ShowCursor(enable);
}
bool sdlgame::mouse::get_visible()
{
    return isVisible;
}