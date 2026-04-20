#include "Button.hpp"
#include "TetrisEvent.hpp"
#include "engine.hpp"

void Button::set_images(const std::shared_ptr<const Surface> &idle,
                        const std::shared_ptr<const Surface> &hover,
                        const std::shared_ptr<const Surface> &click) {
  m_idle = idle;
  m_hover = hover;
  m_click = click;
  m_image = idle;
  m_rect = m_image->get_rect();
}

void Button::handle_event(const Event &event) {
  if (event.type == sdlgame::MOUSEBUTTONDOWN and hovering) {
    m_image = m_click;
  } else if (event.type == sdlgame::MOUSEBUTTONUP and hovering) {
    sdlgame::event::post(BUTTON_CLICK);
    on_click();
  }
}
void Button::update() {
  sdlgame::math::Vector2 mouse_pos = sdlgame::mouse::get_pos();
  if (m_rect.collidepoint(mouse_pos))
    hovering = 1;
  else {
    m_image = m_idle;
    hovering = 0;
  }
  if (hovering and !prev_hovered) {
    m_image = m_hover;
    sdlgame::event::post(BUTTON_HOVER);
  }
  prev_hovered = hovering;
}