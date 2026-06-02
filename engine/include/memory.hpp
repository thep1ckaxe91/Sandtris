#pragma once
#ifndef SDLGAME_MEMORY_
#define SDLGAME_MEMORY_
#include "SDL2/SDL.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

namespace sdlgame::memory {
template <typename T> struct SDLTraits;

template <> struct SDLTraits<SDL_Texture> {
  static void Free(SDL_Texture *p) { SDL_DestroyTexture(p); }
};

template <> struct SDLTraits<SDL_Renderer> {
  static void Free(SDL_Renderer *p) { SDL_DestroyRenderer(p); }
};

template <> struct SDLTraits<SDL_Window> {
  static void Free(SDL_Window *p) { SDL_DestroyWindow(p); }
};

template <> struct SDLTraits<SDL_Surface> {
  static void Free(SDL_Surface *p) { SDL_FreeSurface(p); }
};

template <> struct SDLTraits<Mix_Music> {
  static void Free(Mix_Music *p) { Mix_FreeMusic(p); }
};

template <> struct SDLTraits<Mix_Chunk> {
  static void Free(Mix_Chunk *p) { Mix_FreeChunk(p); }
};

template <> struct SDLTraits<TTF_Font> {
  static void Free(TTF_Font *p) { TTF_CloseFont(p); }
};

struct SDLDeleter {
  template <typename T> void operator()(T *ptr) const {
    if (ptr) {
      SDLTraits<T>::Free(ptr);
    }
  }
};

template <typename T> using SDLUniquePtr = std::unique_ptr<T, SDLDeleter>;

template <typename T> using SDLSharedPtr = std::shared_ptr<T>;
} // namespace sdlgame::memory

#endif