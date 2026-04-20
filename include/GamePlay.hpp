#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP
#include "Animation.hpp"
#include "Game.hpp"
#include "Grid.hpp"
#include "PauseButton.hpp"
#include "Scene.hpp"
#include "engine.hpp"
class GamePlay : public Scene {
private:
  Vector2 m_bg_offset;
  Color m_next_color;
  Surface m_next_shape_surf;
  Grid m_grid;
  Font m_score_font;
  Surface m_score_surf;
  Rect m_score_rect;
  PauseButton m_pause_button;
  SandShift m_next_display_color;
  Rect m_flow1, m_flow2;
  Animation m_change_shape;
  Animation m_count_down;
  Color m_color_flow1;
  Color m_color_flow2;
  int m_blipcount;
  static constexpr int s_flow_speed = 48; // pps
  bool m_gameover;
  bool m_pausing;

public:
  GamePlay(Game &game);
  void redraw_next_shape();
  void update();
  void draw();
  void load_grid(Grid grid);
  void handle_event(sdlgame::event::Event &event);
  ~GamePlay();
};

#endif