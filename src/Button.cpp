#include "Button.hpp"
#include "TetrisEvent.hpp"
#include <sdlgame/mouse.hpp>
#include <sdlgame/surface.hpp>

template <SDL_TextureAccess Ac> using Surface = sdlgame::surface::Surface<Ac>;

Button::Button()
    : m_idle(nullptr), m_hover(nullptr), m_click(nullptr), hovering(false),
      prev_hovered(false) {}

void Button::set_images(
    std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> idle,
    std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> hover,
    std::shared_ptr<Surface<SDL_TEXTUREACCESS_STATIC>> click) {
  m_idle = idle;
  m_hover = hover;
  m_click = click;
  m_image = idle;
  m_rect = m_image->get_rect();
}

void Button::handle_event(const sdlgame::event::Event &event) {
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