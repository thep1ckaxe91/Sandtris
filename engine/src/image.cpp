#include "image.hpp"
#include "SDL_image.h"
#include "display.hpp"
#include "surface.hpp"
#include <filesystem>
#include <stdio.h>

namespace fs = std::filesystem;

namespace sdlgame::image {
void init() {
  if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
    printf("Failed to init JPG image flags\n%s\n", IMG_GetError());
    exit(0);
  } else if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("Failed to init PNG image flags\n%s\n", IMG_GetError());
    exit(0);
  } else {
    printf("Image successfully initialized\n");
    return;
  }
}
// sdlgame::surface::Surface img_transfer_surf;
[[nodiscard]] sdlgame::surface::Surface load(const fs::path path) {
  SDL_Texture *tex =
      IMG_LoadTexture(sdlgame::display::renderer.get(), path.c_str());
  if (tex == nullptr) {
    printf("Cant load image\n%s\n", IMG_GetError());
    exit(0);
  }
  // img_transfer_surf =sdlgame::surface::Surface(tex);
  return sdlgame::surface::Surface(tex);
}
} // namespace sdlgame::image