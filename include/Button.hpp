#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "engine.hpp"
class Button : public sdlgame::sprite::Sprite {
public:
  std::shared_ptr<const Surface> m_idle;
  std::shared_ptr<const Surface> m_hover;
  std::shared_ptr<const Surface> m_click;
  bool hovering, prev_hovered;
  Button() = default;
  virtual void on_click() = 0;
  void set_images(const std::shared_ptr<const Surface> &idle,
                  const std::shared_ptr<const Surface> &hover,
                  const std::shared_ptr<const Surface> &click);
  virtual void handle_event(const Event &event);
  virtual void update();
};

#endif