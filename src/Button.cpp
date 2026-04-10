#include "Button.hpp"
#include "engine.hpp"
#include "TetrisEvent.hpp"
Button::Button()
{
    hovering = prev_hovered = 0;
    idle = nullptr;
    hover = nullptr;
    click = nullptr;
}
void Button::set_images(Surface &idle, Surface &hover, Surface &click)
{
    idle = &idle;
    hover = &hover;
    click = &click;
    image = idle;
    rect = (*image).get_rect();
}

void Button::handle_event(Event &event)
{
    if (event.type == sdlgame::MOUSEBUTTONDOWN and hovering)
    {
        image = click;
    }
    else if (event.type == sdlgame::MOUSEBUTTONUP and hovering)
    {
        sdlgame::event::post(BUTTON_CLICK);
        on_click();
    }
}
void Button::update()
{
    math::Vector2 mouse_pos = sdlgame::mouse::get_pos();
    if (rect.collidepoint(mouse_pos))
        hovering = 1;
    else
    {
        image = idle;
        hovering = 0;
    }
    if (hovering and !prev_hovered)
    {
        image = hover;
        sdlgame::event::post(BUTTON_HOVER);
    }
    prev_hovered = hovering;
}