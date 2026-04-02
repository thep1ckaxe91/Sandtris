#pragma once
#ifndef SDLGAME_IMAGE_
#define SDLGAME_IMAGE_
#include "surface.hpp"
#include <string>
namespace sdlgame::image {
/**
 * Currently only support JPG and PNG type
 */
void init();
/**
 * load an image from file path, require you to create the window object first
 */
sdlgame::surface::Surface load(std::string path);
} // namespace sdlgame::image

#endif