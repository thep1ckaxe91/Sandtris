#pragma once
#ifndef SDLGAME_COLOR_
#define SDLGAME_COLOR_
#include "SDL2/SDL.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
namespace sdlgame{
    namespace color
    {
        extern std::map<std::string, std::vector<uint8_t>> color_name;
        void init();
        /**
         *  class for color, all values range from [0,255]
         */
        class Color
        {
        public:
            Uint8 r, g, b, a;
            Color();
            Color(const char *c_name);
            Color(std::string name);
            Color(int _r, int _g, int _b);
            Color(int _r, int _g, int _b, int _a);
            
            SDL_Color to_SDL_Color() const;
            /**return Uint32 kind of color*/
            Uint32 toUint32Color() const;
            std::string toString();
            /**
             * @brief add r g b value to the current color, the value will be clamp in range 0,255
             * 
             * @param r add red value
             * @param g add green
             * @param b add blue
             * @return Color that have the value of original red + r ...
             */
            Color add_value(Uint8 r, Uint8 g, Uint8 b);
        };
    }
}

#endif