#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "engine.hpp"
#include <memory>

class Button : public sdlgame::sprite::Sprite {
public:
  std::shared_ptr<const sdlgame::surface::Surface> m_idle;
  std::shared_ptr<const sdlgame::surface::Surface> m_hover;
  std::shared_ptr<const sdlgame::surface::Surface> m_click;
  bool hovering, prev_hovered;
  Button();
  virtual void on_click() = 0;
  void set_images(std::shared_ptr<const sdlgame::surface::Surface> idle,
                  std::shared_ptr<const sdlgame::surface::Surface> hover,
                  std::shared_ptr<const sdlgame::surface::Surface> click);
  virtual void handle_event(const Event &event);
  virtual void update();
};

#endif