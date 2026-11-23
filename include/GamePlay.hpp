#pragma once
#include <SDL_render.h>
#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP
#include "Animation.hpp"
#include "Game.hpp"
#include "Grid.hpp"
#include "PauseButton.hpp"
#include "Scene.hpp"
#include <memory>
#include <sdlgame/font.hpp>

class GamePlay : public Scene {
private:
  static constexpr int s_flow_speed = 48; // pps
  
  Grid m_grid;
  
  sdlgame::math::Vector2 m_bg_offset;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_TARGET> m_next_shape_surf;
  sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC> m_score_surf;
  sdlgame::font::Font m_score_font;
  sdlgame::rect::Rect m_score_rect;
  sdlgame::rect::Rect m_flow1, m_flow2;
  std::shared_ptr<PauseButton> m_pause_button;
  std::shared_ptr<Animation> m_change_shape;
  std::shared_ptr<Animation> m_count_down;
  sdlgame::color::Color m_color_flow1;
  sdlgame::color::Color m_color_flow2;
  sdlgame::color::Color m_next_color;
  int m_blipcount;
  SandShift m_next_display_color;
  bool m_gameover;
  bool m_pausing;

public:
  GamePlay(Game &game);
  void redraw_next_shape();
  void update() override;
  void draw() override;
  void load_grid(Grid grid);
  void handle_event(const sdlgame::event::Event &event) override;
  ~GamePlay() override;
};

#endif
