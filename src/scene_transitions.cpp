#include "scene_transitions.hpp"
using Event = sdlgame::event::Event;
using Rect = sdlgame::rect::Rect;
using Vector2 = sdlgame::math::Vector2;
using Surface = sdlgame::surface::Surface;
using Color = sdlgame::color::Color;
using Sound = sdlgame::mixer::Sound;
using Channel = sdlgame::mixer::Channel;
using Font = sdlgame::font::Font;
using namespace std;
OutSwipeDown::OutSwipeDown(double time) : SceneTransition(time)
{
    vel=cur_height=0;
    this->accelerate = (sdlgame::display::get_height()*2/(time*time));
}
void OutSwipeDown::update(double delta_time)
{
    this->vel += this->accelerate * delta_time;
    this->time -= delta_time;
    if(this->time <= 0) isDone = 1;
    // cout << this->vel << " " << this->accelerate << " " << delta_time << endl;
    this->cur_height += this->vel*delta_time;
}
void OutSwipeDown::draw()
{
    sdlgame::draw::rect(sdlgame::display::get_surf(),"black",Rect(0.0,0.0,sdlgame::display::get_width(),cur_height));
}
InSwipeDown::InSwipeDown(double time) : SceneTransition(time)
{
    vel=cur_height=0;
    this->accelerate = (sdlgame::display::get_height()*2)/time/time;
}
void InSwipeDown::update(double delta_time)
{
    this->vel += this->accelerate * delta_time;
    this->time -= delta_time;
    if(this->time <= 0) isDone = 1;

    this->cur_height += this->vel*delta_time;
}
void InSwipeDown::draw()
{
    sdlgame::draw::rect(sdlgame::display::get_surf(),"black",Rect(0.0,cur_height,sdlgame::display::get_width(),sdlgame::display::get_height()));
}

OutFade::OutFade(double time) : SceneTransition(time)
{
    this->mask = Surface(sdlgame::display::get_width(),sdlgame::display::get_height());
    this->cur_color = Color("none");
    this->mask.fill(cur_color);
    this->vel = 255/this->time;
    cur_alpha=0;
}
void OutFade::update(double delta_time)
{
    this->cur_alpha += this->vel*delta_time;
    this->cur_color.a = Uint8(cur_alpha);
    this->time -= delta_time;
    this->mask.fill(this->cur_color);
    if(this->time<=0)
    {
        this->isDone=1;
    }
}
void OutFade::draw()
{
    sdlgame::display::get_surf().blit(this->mask,Vector2());
}

InFade::InFade(double time) : SceneTransition(time)
{
    this->mask = Surface(sdlgame::display::get_width(),sdlgame::display::get_height());
    this->cur_color = Color("black");
    this->mask.fill(cur_color);
    this->vel = -255/this->time;
    cur_alpha=255;
}
void InFade::update(double delta_time)
{
    this->cur_alpha += this->vel * delta_time;
    this->cur_color.a = Uint8(cur_alpha);
    this->time -= delta_time;
    this->mask.fill(this->cur_color);
    if(this->time<=0)
    {
        this->isDone=1;
    }
}
void InFade::draw()
{
    sdlgame::display::get_surf().blit(this->mask,Vector2());
}
