#include "display.hpp"
#include <stdio.h>
#include "SDL2/SDL_hints.h"
#include "SDL2/SDL_image.h"
#include "surface.hpp"
#include "math.hpp"
SDL_Window *sdlgame::display::window;
SDL_Renderer *sdlgame::display::renderer;
sdlgame::surface::Surface sdlgame::display::win_surf;
bool sdlgame::display::isInit;
sdlgame::math::Vector2 sdlgame::display::resolution;

/**
 * Setup a window surface for use
 * @param width the resolution width of the window
 * @param height the resolution height of the window
 * @param flags flags for the window, look for Window_Flags enum for more
 * @return a surface that represent the window, what action affect this window will affect what display on screen
 */
sdlgame::surface::Surface &sdlgame::display::set_mode(int width, int height, Uint32 flags)
{
    if (width == 0 || height == 0)
    {
        SDL_DisplayMode DM;
        SDL_GetDesktopDisplayMode(0, &DM);
        width = DM.w;
        height = DM.h;
    }
    resolution = sdlgame::math::Vector2(width, height);
    if(!SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER,"direct3d11",SDL_HINT_OVERRIDE))
    {
        printf("Set renderer driver hint failed\n");
    }
    window = SDL_CreateWindow("SDLgame Custom Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (window == nullptr)
    {
        printf("Failed to create a window object\nErr: %s\n", SDL_GetError());
        exit(0);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (renderer == nullptr)
    {
        printf("Failed to create a renderer\nErr: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_RenderSetLogicalSize(renderer, width, height);
    // printf("Initialize window and renderer: %p %p\n",window,renderer);
    win_surf.texture = NULL; // THIS IS INTENDED!
    win_surf.size.x = width;
    win_surf.size.y = height;
    return win_surf;
}
bool sdlgame::display::set_render_scale_quality(bool linear)
{
    if (linear)
        return SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "linear", SDL_HINT_OVERRIDE);
    return SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "nearest", SDL_HINT_OVERRIDE);
}
void sdlgame::display::maximize()
{
    SDL_SetWindowFullscreen(window, 0);
    SDL_MaximizeWindow(window);
}

void sdlgame::display::minimize()
{
    SDL_SetWindowFullscreen(window, 0);
    SDL_MinimizeWindow(window);
}
void sdlgame::display::restore()
{
    SDL_SetWindowFullscreen(window, 0);
    SDL_RestoreWindow(window);
}
void sdlgame::display::fullscreen()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}
bool sdlgame::display::is_fullscreen()
{
    return (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) || (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN);
}
void sdlgame::display::set_window_size(int w,int h)
{
    SDL_SetWindowSize(sdlgame::display::window,w,h);
}
//set position of window, use sdlgame::WINDOWPOS_CENTERED if you need center
void sdlgame::display::set_window_pos(int x,int y)
{
    SDL_SetWindowPosition(sdlgame::display::window,x,y);
}
std::pair<int,int> sdlgame::display::get_window_pos()
{
    int x,y;
    SDL_GetWindowPosition(sdlgame::display::window,&x,&y);
    return {x,y};
}
sdlgame::math::Vector2 sdlgame::display::get_window_size()
{
    int w, h;
    SDL_GetWindowSize(sdlgame::display::window, &w, &h);
    // SDL_GetWindowSurface(sdlgame::display::window);
    return win_surf.size = sdlgame::math::Vector2(w, h);
}

void sdlgame::display::fullscreen_desktop()
{
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}
sdlgame::surface::Surface &sdlgame::display::get_surf()
{
    return win_surf;
}

double sdlgame::display::get_width()
{
    if (win_surf.getWidth() == 0)
    {
        printf("Display not yet set mode\n");
        exit(0);
    }
    return win_surf.getWidth();
}
double sdlgame::display::get_height()
{
    if (win_surf.getHeight() == 0)
    {
        printf("Display not yet set mode\n");
        exit(0);
    }
    return win_surf.getHeight();
}
/**
 *  if set to true, the mouse will be confine to the window
 * this function get or set the state of mouse being confine or not
 *
 */
bool sdlgame::display::grab(int enable)
{
    if (enable == -1)
        return SDL_GetWindowGrab(window);
    SDL_SetWindowGrab(window, (enable ? SDL_TRUE : SDL_FALSE));
    return enable;
}

void sdlgame::display::set_icon(const char *icon_path)
{
    SDL_Surface *icon = IMG_Load(icon_path);
    SDL_SetWindowIcon(window, icon);
}

/**
 *  get and set the borderless state of the active window;
 */
bool sdlgame::display::borderless(int enable)
{
    if (enable == -1)
        return (SDL_GetWindowFlags(window) & SDL_WINDOW_BORDERLESS);
    SDL_SetWindowBordered(window, (enable ? SDL_FALSE : SDL_TRUE));
    return (SDL_GetWindowFlags(window) & SDL_WINDOW_BORDERLESS) > 0;
}
void sdlgame::display::set_caption(const char *title)
{
    SDL_SetWindowTitle(window, title);
}
SDL_Window *sdlgame::display::get_window()
{
    return window;
}
SDL_Renderer *sdlgame::display::get_renderer()
{
    return renderer;
}
void sdlgame::display::quit()
{
    if (window)
        SDL_DestroyWindow(window);
    if (renderer)
        SDL_DestroyRenderer(renderer);
}
void sdlgame::display::flip()
{
    if (SDL_GetRenderTarget(renderer))
        SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderPresent(renderer);
}