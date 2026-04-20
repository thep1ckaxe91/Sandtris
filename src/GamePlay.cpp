#include "GamePlay.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "Grid.hpp"
#include "PauseButton.hpp"
#include "SaveData.hpp"
#include "TetrisEvent.hpp"
#include "color.hpp"
#include "constant.hpp"
#include "font.hpp"
#include "scene_transitions.hpp"
#include <iostream>
#include <memory>

GamePlay::GamePlay(Game &game)
    : Scene(game), m_change_shape(game, 120), m_color_flow1("none"s),
      m_color_flow2("none"s), m_grid(game), m_count_down(game, 1),
      m_pause_button(game), m_gameover(false), m_blipcount(100),
      m_pausing(false),
      m_score_font(base_path / "assets" / "fonts" / "sandtris pixel.ttf",
                   FONT_SIZE) {

  m_score_surf =
      m_score_font.render("0", sdlgame::font::AntiAlias::SOLID, "white"s);
  m_score_rect = m_score_surf.get_rect();
  m_score_rect.setCenter(score_display_center);

  m_next_display_color = m_grid.next.color;
  m_flow1 = next_color_display_rect.inflate(0, 5);
  m_flow2 = m_flow1.move(0, next_color_display_rect.getHeight());

  m_next_shape_surf = Surface(next_shape_display_rect.getWidth(),
                              next_shape_display_rect.getHeight());
  redraw_next_shape();
  m_change_shape.load(base_path / "assets" / "animations" /
                      "change_next_shape");
  auto tmp = std::make_shared<Surface>(next_shape_display_area.getWidth(),
                                       next_shape_display_area.getHeight());
  tmp->fill("none"s);
  m_change_shape.set_default_image(tmp);

  m_count_down.load(base_path / "assets" / "animations" / "count_down");
  tmp = std::make_shared<Surface>(count_down_display_rect.getWidth(),
                                  count_down_display_rect.getHeight());
  tmp->fill("none"s);
  m_count_down.set_default_image(tmp);
  m_count_down.play();

  sdlgame::music::load(base_path / "assets" / "audio" / "music" /
                       "tetris_theme_loop_instrument.mp3");
  sdlgame::music::play(-1, 2000);

  m_pause_button.get_rect().setTopRight(RESOLUTION_WIDTH, 0);
}
void GamePlay::load_grid(Grid grid) {
  std::cerr << "Load grid have not yet implemented, or rather, find a better "
               "way to implement load grid from memory.\nThe current state of "
               "SaveData isnt good anyway\n";
}
void GamePlay::redraw_next_shape() {
  m_next_shape_surf.fill(Color());
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (m_grid.next.mask >> (15 - i * 4 - j) & 1)
        sdlgame::draw::rect(
            m_next_shape_surf, Color("white"),
            Rect(Vector2(6 * j, 6 * i) +
                     (m_grid.next.type != 'I' and m_grid.next.type != 'O'
                          ? Vector2(4, 1)
                          : Vector2()),
                 6, 6));
}
void GamePlay::handle_event(sdlgame::event::Event &event) {
  if (!m_count_down.is_playing()) {
    m_grid.handle_event(event);
    m_pause_button.handle_event(event);
  }
  if (event.type == SCORING) {
    m_score_surf =
        m_score_font.render(std::to_string(m_grid.get_score()),
                            sdlgame::font::AntiAlias::SOLID, "white"s);
    m_score_rect = m_score_surf.get_rect();
    m_score_rect.setCenter(score_display_center);
    if (get_personal_best() < m_grid.get_score())
      set_personal_best(m_grid.get_score());
  } else if (event.type == MERGING) {
    m_next_display_color = m_grid.next.color;
    redraw_next_shape();
    m_change_shape.play();
  } else if (event.type == GAMEOVER) {
    sdlgame::music::stop();
    delete_grid_data();
    m_gameover = 1;
  } else if (event.type == BUTTON_CLICK) {
    sdlgame::music::pause();
    m_pausing = 1;
    save_grid_data(m_grid);
  } else if (event.type == sdlgame::KEYDOWN) {
    if ((event["key"] == sdlgame::K_p or event["key"] == sdlgame::K_ESCAPE) and
        !game.in_transitioning() and !game.out_transitioning() and
        !m_gameover) {
      m_pause_button.on_click();
      sdlgame::music::pause();
      m_pausing = 1;
      save_grid_data(m_grid);
    }
  }
}
void GamePlay::update() {
  if (m_pausing and is_working() and
      !(game.out_transitioning() or game.in_transitioning())) {
    m_pausing = 0;
    m_count_down.reset();
    m_count_down.play();
  }
  if (!m_gameover) {
    if (!m_count_down.is_playing() and !m_pausing) {
      sdlgame::music::resume();
      m_grid.update();
      double delta_y = -s_flow_speed * game.m_clock.delta_time().count();
      m_flow1.move_ip(0, delta_y);
      m_flow2.move_ip(0, delta_y);
      if (m_flow1.getBottom() - 1 <= next_color_display_rect.getTop()) {
        m_flow1.setTop(m_flow2.getBottom());
        m_color_flow1 =
            SandShiftColor.at(static_cast<uint8_t>(m_next_display_color));
      }
      if (m_flow2.getBottom() - 1 <= next_color_display_rect.getTop()) {
        m_flow2.setTop(m_flow1.getBottom());
        m_color_flow2 =
            SandShiftColor.at(static_cast<uint8_t>(m_next_display_color));
      }
      m_change_shape.update();
    } else {
      if (m_count_down.frame_changed()) {
        if (m_count_down.get_frame_index() != 4)
          sdlgame::event::post(COUNT_DOWN);
        else
          sdlgame::event::post(COUNT_DOWN_START);
      }
      m_count_down.update();
    }
    m_bg_offset.x -= gameplay_bg_speed * game.m_clock.delta_time().count();
    m_bg_offset.y -= gameplay_bg_speed * game.m_clock.delta_time().count();
    if (m_bg_offset.x <= -8)
      m_bg_offset = Vector2();
    m_pause_button.update();
  } else {
    m_blipcount--;
  }
}
void GamePlay::draw() {
  game.m_window.blit(game.m_images.gameplay_background, m_bg_offset);

  sdlgame::draw::rect(game.m_window, m_color_flow1,
                      m_flow1.overlap(next_color_display_rect));
  sdlgame::draw::rect(game.m_window, m_color_flow2,
                      m_flow2.overlap(next_color_display_rect));

  game.m_window.blit(game.m_images.game_frame, Vector2());

  game.m_window.blit(m_next_shape_surf, next_shape_display_rect.getTopLeft());

  game.m_window.blit((m_change_shape.get_image()),
                     next_shape_display_area.getTopLeft());
  if (!(m_blipcount / 10 & 1) and m_blipcount >= 0)
    m_grid.draw();

  if (m_count_down.is_playing())
    game.m_window.blit((m_count_down.get_image()),
                       count_down_display_rect.getTopLeft());

  if (m_blipcount == -1) {
    auto out = std::make_unique<OutSwipeDown>();
    auto in = std::make_unique<InSwipeDown>();
    std::unique_ptr<Scene> next =
        std::make_unique<GameOver>(game, m_grid.get_score());
    game.pop_scene(std::move(out), std::move(next), std::move(in));
  }

  game.m_window.blit((m_pause_button.get_image()),
                     m_pause_button.get_rect().getTopLeft());
  game.m_window.blit(m_score_surf, m_score_rect.getTopLeft());
}

GamePlay::~GamePlay() {
  // sdlgame::music::stop();
}