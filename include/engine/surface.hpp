#pragma once
#ifndef SDLGAME_SURFACE_
#define SDLGAME_SURFACE_
#include "SDL2/SDL.h"
#include "color.hpp"
#include "rect.hpp"
#include "math.hpp"
#define SURFACE_TYPE SDL_TEXTUREACCESS_TARGET
namespace sdlgame
{
    namespace surface
    {
        /**
         * @brief since the problem mostly related to the heavy draw and surface manage in pygame
         * this module is mostly focus optimiszing the surface class, the texture pointer should be null if the surface is represent window
         * after set_mode is called
         */
        class Surface
        {
        public:
            sdlgame::math::Vector2 size;
            SDL_Texture *texture;
            Surface();

            Surface(int width, int height);

            Surface(const Surface &oth);

            Surface(SDL_Texture *oth);

            Surface(SDL_Surface *surf);
            Surface &operator=(const Surface &other);
            /**
             * Return a copy of the surface rect
             */
            sdlgame::rect::Rect getRect() const;
            /**
             * Blit a surface onto this surface with position and size, leave size be -1,-1 will be its original size
             * the surface or image will stretch or shrink acoording to the size
             */
            void blit(Surface &source, sdlgame::math::Vector2 pos, sdlgame::math::Vector2 size = sdlgame::math::Vector2(-1, -1), sdlgame::rect::Rect area = sdlgame::rect::Rect());
            void fill(sdlgame::color::Color color);
            sdlgame::math::Vector2 get_size() const;
            double getWidth() const;
            double getHeight() const;
            ~Surface();
        };
    }
}

#endif