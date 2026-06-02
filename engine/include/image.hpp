#pragma once
#ifndef SDLGAME_IMAGE_
#define SDLGAME_IMAGE_
#include "surface.hpp"
#include <string>
#include <filesystem>
#include <memory>
namespace sdlgame::image {
/**
 * Currently only support JPG and PNG type
 */
void init();
/**
 * load an image from file path, require you to create the window object first
 */
std::shared_ptr<const surface::Surface> load(const std::filesystem::path path);
} // namespace sdlgame::image

#endif