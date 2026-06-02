#include "display.hpp"
#include "SDL2/SDL_hints.h"
#include "SDL2/SDL_image.h"
#include "math.hpp"
#include "memory.hpp"
#include "surface.hpp"
#include <iostream>

namespace sdlgame::display {
namespace {
sdlgame::memory::SDLUniquePtr<SDL_Window> window = nullptr;
sdlgame::memory::SDLUniquePtr<SDL_Renderer> renderer = nullptr;

sdlgame::surface::Surface proxy_surf;
bool isInit;
math::Vector2 resolution;
} // namespace

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

  resolution = math::Vector2(width, height);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

  window.reset(SDL_CreateWindow("SDLgame", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height, flags));

  if (!window) {
    std::cerr << "Fatal: Window creation failed: " << SDL_GetError() << "\n";
    exit(1);
  }

  renderer.reset(SDL_CreateRenderer(
      window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  if (!renderer) {
    std::cerr << "Fatal: Renderer creation failed: " << SDL_GetError() << "\n";
    exit(1);
  }

  SDL_RenderSetLogicalSize(renderer.get(), width, height);

  // Fulfill the Pygame syntax requirement
  proxy_surf.size = math::Vector2(width, height);
  return proxy_surf;
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
math::Vector2 get_window_size() {
  int w, h;
  SDL_GetWindowSize(window.get(), &w, &h);
  // SDL_GetWindowSurface(window.get());
  return proxy_surf.size = math::Vector2(w, h);
}

void fullscreen_desktop() {
  SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
}
sdlgame::surface::Surface &get_surf() { return proxy_surf; }

double get_width() {
  if (proxy_surf.get_width() == 0) {
    printf("Display not yet set mode\n");
    exit(0);
  }
  return proxy_surf.get_width();
}
double get_height() {
  if (proxy_surf.get_height() == 0) {
    printf("Display not yet set mode\n");
    exit(0);
  }
  return proxy_surf.get_height();
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

void set_icon(const fs::path &icon_path) {
  sdlgame::memory::SDLUniquePtr<SDL_Surface> icon(
      IMG_Load(icon_path.string().c_str()));
  SDL_SetWindowIcon(window.get(), icon.get());
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
void set_caption(const std::string &title) {
  SDL_SetWindowTitle(window.get(), title.c_str());
}
SDL_Window *get_window() { return window.get(); }
SDL_Renderer *get_renderer() { return renderer.get(); }
void quit() {
  window.reset();
  renderer.reset();
}
void flip() {
  SDL_SetRenderTarget(renderer.get(), nullptr);
  SDL_RenderPresent(renderer.get());
}
} // namespace sdlgame::display