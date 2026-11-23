#pragma once
#include <SDL_render.h>
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <sdlgame/event.hpp>
#include <sdlgame/sprite.hpp>
#include <sdlgame/surface.hpp>

using sdlgame::surface::Surface;

class Button : public sdlgame::sprite::Sprite {
public:
  std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> m_idle;
  std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> m_hover;
  std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> m_click;
  bool hovering, prev_hovered;
  Button();
  virtual void on_click() = 0;
  void
  set_images(const std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> &idle,
             const std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> &hover,
             const std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> &click);
  virtual void handle_event(const sdlgame::event::Event &event);
  virtual void update();
};

#endif