#ifndef SDLGAME_MEMORY_
#define SDLGAME_MEMORY_
#include "SDL2/SDL.h"
#include <memory>

namespace sdlgame::memory
{
    template <typename T>
    struct SDLTraits;

    template <>
    struct SDLTraits<SDL_Texture>
    {
        static void Free(SDL_Texture *p) { SDL_DestroyTexture(p); }
    };

    template <>
    struct SDLTraits<SDL_Renderer>
    {
        static void Free(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
    };

    template <>
    struct SDLTraits<SDL_Window>
    {
        static void Free(SDL_Window *p) { SDL_DestroyWindow(p); }
    };

    struct SDLDeleter
    {
        template <typename T>
        void operator()(T *ptr) const
        {
            if (ptr)
            {
                SDLTraits<T>::Free(ptr);
            }
        }
    };

    template<typename T>
    using SDLUniquePtr = std::unique_ptr<T, SDLDeleter>;    
}

#endif