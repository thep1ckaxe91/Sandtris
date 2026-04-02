#include "display.hpp"
#include "SDL2/SDL_hints.h"
#include "SDL2/SDL_image.h"
#include "math.hpp"
#include "surface.hpp"
#include <stdio.h>

namespace sdlgame::display {
sdlgame::memory::SDLUniquePtr<SDL_Window> window = nullptr;
sdlgame::memory::SDLUniquePtr<SDL_Renderer> renderer = nullptr;

sdlgame::surface::Surface win_surf;
bool isInit;
sdlgame::math::Vector2 resolution;

/**
 * Setup a window surface for use
 * @param width the resolution width of the window
 * @param height the resolution height of the window
 * @param flags flags for the window, look for Window_Flags enum for more
 * @return a surface that represent the window, what action affect this window
 * will affect what display on screen
 */
sdlgame::surface::Surface &set_mode(int width, int height, uint32_t flags) {
  if (width == 0 || height == 0) {
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    width = DM.w;
    height = DM.h;
  }
  resolution = sdlgame::math::Vector2(width, height);
  if (!SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "direct3d11",
                               SDL_HINT_NORMAL)) {
    printf("Set renderer driver hint failed\n");
  }
  window.reset(SDL_CreateWindow("SDLgame Custom Engine", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height, flags));
  if (window == nullptr) {
    printf("Failed to create a window object\nErr: %s\n", SDL_GetError());
    exit(0);
  }
  renderer.reset(SDL_CreateRenderer(
      window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE));
  if (renderer == nullptr) {
    printf("Failed to create a renderer\nErr: %s\n", SDL_GetError());
    exit(0);
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,
              "nearest"); // TODO: this could very well be a graphic option
  SDL_SetHint(SDL_HINT_RENDER_VSYNC,
              "0"); // TODO: same, can be a settings option

  SDL_RenderSetLogicalSize(renderer.get(), width, height);
  // printf("Initialize window and renderer: %p %p\n",window,renderer);
  win_surf.texture.reset(); // THIS IS INTENDED!
  win_surf.size.x = width;
  win_surf.size.y = height;
  return win_surf;
}
bool set_render_scale_quality(bool linear) {
  if (linear)
    return SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "linear",
                                   SDL_HINT_OVERRIDE);
  return SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "nearest",
                                 SDL_HINT_OVERRIDE);
}
void maximize() {
  SDL_SetWindowFullscreen(window.get(), 0);
  SDL_MaximizeWindow(window.get());
}

void minimize() {
  SDL_SetWindowFullscreen(window.get(), 0);
  SDL_MinimizeWindow(window.get());
}
void restore() {
  SDL_SetWindowFullscreen(window.get(), 0);
  SDL_RestoreWindow(window.get());
}
void fullscreen() {
  SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN);
}
bool is_fullscreen() {
  return (SDL_GetWindowFlags(window.get()) & SDL_WINDOW_FULLSCREEN_DESKTOP) ||
         (SDL_GetWindowFlags(window.get()) & SDL_WINDOW_FULLSCREEN);
}
void set_window_size(int w, int h) { SDL_SetWindowSize(window.get(), w, h); }
// set position of window, use sdlgame::WINDOWPOS_CENTERED if you need center
void set_window_pos(int x, int y) { SDL_SetWindowPosition(window.get(), x, y); }
std::pair<int, int> get_window_pos() {
  int x, y;
  SDL_GetWindowPosition(window.get(), &x, &y);
  return {x, y};
}
sdlgame::math::Vector2 get_window_size() {
  int w, h;
  SDL_GetWindowSize(window.get(), &w, &h);
  // SDL_GetWindowSurface(window.get());
  return win_surf.size = sdlgame::math::Vector2(w, h);
}

void fullscreen_desktop() {
  SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
}
sdlgame::surface::Surface &get_surf() { return win_surf; }

double get_width() {
  if (win_surf.getWidth() == 0) {
    printf("Display not yet set mode\n");
    exit(0);
  }
  return win_surf.getWidth();
}
double get_height() {
  if (win_surf.getHeight() == 0) {
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
bool grab(int enable) {
  if (enable == -1)
    return SDL_GetWindowGrab(window.get());
  SDL_SetWindowGrab(window.get(), (enable ? SDL_TRUE : SDL_FALSE));
  return enable;
}

void set_icon(const char *icon_path) {
  SDL_Surface *icon = IMG_Load(icon_path);
  SDL_SetWindowIcon(window.get(), icon);
}

/**
 *  get and set the borderless state of the active window;
 */
bool borderless(int enable) {
  if (enable == -1)
    return (SDL_GetWindowFlags(window.get()) & SDL_WINDOW_BORDERLESS);
  SDL_SetWindowBordered(window.get(), (enable ? SDL_FALSE : SDL_TRUE));
  return (SDL_GetWindowFlags(window.get()) & SDL_WINDOW_BORDERLESS) > 0;
}
void set_caption(const char *title) { SDL_SetWindowTitle(window.get(), title); }
SDL_Window *get_window() { return window.get(); }
SDL_Renderer *get_renderer() { return renderer.get(); }
void quit() {
  if (window.get())
    SDL_DestroyWindow(window.get());
  if (renderer)
    SDL_DestroyRenderer(renderer.get());
}
void flip() {
  SDL_SetRenderTarget(renderer.get(), nullptr);
  SDL_RenderPresent(renderer.get());
}
} // namespace sdlgame::display