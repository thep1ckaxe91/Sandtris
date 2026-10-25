#pragma once
#include <SDL_render.h>
#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "MenuButton.hpp"
#include "RetryButton.hpp"
#include "Scene.hpp"
#include <memory>
#include <sdlgame/font.hpp>
#include <sdlgame/rect.hpp>
#include <sdlgame/surface.hpp>

class GameOver : public Scene {
  std::shared_ptr<MenuButton> menu;
  std::shared_ptr<RetryButton> retry;
  sdlgame::font::Font score_font;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> new_score_surf;
  sdlgame::rect::Rect new_score_rect;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> pb_surf;
  sdlgame::rect::Rect pb_rect;
  int new_score;
  int pb;

public:
  GameOver(Game &game, int new_score);
  void handle_event(const sdlgame::event::Event &event) override;
  void update() override;
  void draw() override;
};
#endif
