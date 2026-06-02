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
    exit(1);
  } else if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("Failed to init PNG image flags\n%s\n", IMG_GetError());
    exit(1);
  } else {
    printf("Image successfully initialized\n");
    return;
  }
}
// sdlgame::surface::Surface img_transfer_surf;
[[nodiscard]] std::shared_ptr<const surface::Surface> load(const fs::path path) {
  auto tex = IMG_LoadTexture(sdlgame::display::get_renderer(), path.string().c_str());

  if (!tex) {
    printf("Cant load image\n%s\n", IMG_GetError());
    exit(1);
  }
  return std::make_shared<const surface::Surface>(tex);
}
} // namespace sdlgame::image
