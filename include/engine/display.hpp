#pragma once
#ifndef SDLGAME_DISPLAY_
#define SDLGAME_DISPLAY_
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
#include <stdio.h>
#include "surface.hpp"
#include "math.hpp"
namespace sdlgame
{
    namespace display
    {
        extern SDL_Window *window;
        extern SDL_Renderer *renderer;
        extern sdlgame::surface::Surface win_surf;
        extern sdlgame::math::Vector2 resolution;
        extern bool isInit;

        /**
         * Setup a window surface for use
         * @param width the resolution width of the window
         * @param height the resolution height of the window
         * @param flags flags for the window, look for Window_Flags enum for more
         * @return a surface that represent the window, what action affect this window will affect what display on screen
         */
        sdlgame::surface::Surface &set_mode(int width = 0, int height = 0, Uint32 flags = 0);
        /**
         * Maximize the active window
         */
        void maximize();
        /**
         * Minimize the active window
         */
        void minimize();
        void restore();
        void fullscreen();
        void fullscreen_desktop();
        bool is_fullscreen();
        sdlgame::surface::Surface &get_surf();
        //get the actual size in pixel of the window
        sdlgame::math::Vector2 get_window_size();
        //set client window area, not resolution
        void set_window_size(int w,int h);
        void set_window_pos(int x,int y);
        std::pair<int,int> get_window_pos();
        double get_width();
        double get_height();
        /**
         * @brief Set the render scale quality object
         * 
         * @param linear if true, set the scale quality to linear, and nearest if false
         * @return true set success
         * @return false set failed
         */
        bool set_render_scale_quality(bool linear);
        /**
         *  if set to true, the mouse will be confine to the window
         * this function get or set the state of mouse being confine or not
         *
         */
        bool grab(int enable = -1);

        void set_icon(const char *icon_path);
        /**
         *  get and set the borderless state of the active window;
         */
        bool borderless(int enable = -1);
        void set_caption(const char *title);
        SDL_Window *get_window();
        SDL_Renderer *get_renderer();
        void quit();
        void flip();
    }
}


#endif