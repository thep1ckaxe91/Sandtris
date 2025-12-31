#include "Button.hpp"
#include "engine/engine.hpp"
#include "TetrisEvent.hpp"
Button::Button()
{
    hovering = prev_hovered = 0;
    this->idle = nullptr;
    this->hover = nullptr;
    this->click = nullptr;
}
void Button::set_images(Surface &idle, Surface &hover, Surface &click)
{
    this->idle = &idle;
    this->hover = &hover;
    this->click = &click;
    this->image = idle;
    this->rect = this->image.getRect();
}

void Button::handle_event(Event &event)
{
    if (event.type == sdlgame::MOUSEBUTTONDOWN and this->hovering)
    {
        this->image = *this->click;
    }
    else if (event.type == sdlgame::MOUSEBUTTONUP and this->hovering)
    {
        sdlgame::event::post(BUTTON_CLICK);
        this->on_click();
    }
}
void Button::update()
{
    sdlgame::math::Vector2 mouse_pos = sdlgame::mouse::get_pos();
    if (this->rect.collidepoint(mouse_pos))
        this->hovering = 1;
    else
    {
        this->image = *this->idle;
        this->hovering = 0;
    }
    if (this->hovering and !this->prev_hovered)
    {
        this->image = *this->hover;
        sdlgame::event::post(BUTTON_HOVER);
    }
    this->prev_hovered = this->hovering;
}