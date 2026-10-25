#pragma once
#include <font.hpp>
#include <surface.hpp>
#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "BackButton.hpp"
#include "MenuButton.hpp"
#include "OptionButton.hpp"
#include "RetryButton.hpp"
#include "Scene.hpp"
#include <memory>

class Pause : public Scene {
public:
  std::shared_ptr<MenuButton> menu_button;
  std::string message;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> message_surf;
  sdlgame::font::Font message_font;
  sdlgame::rect::Rect message_rect;
  std::shared_ptr<OptionButton> option_button;
  std::shared_ptr<RetryButton> retry_button;
  std::shared_ptr<BackButton> back_button;
  Pause(Game &game);
  void render_message(std::string new_message);
  void display_message();
  void update() override;
  void handle_event(const sdlgame::event::Event &event) override;
  void draw() override;
};

#endif
