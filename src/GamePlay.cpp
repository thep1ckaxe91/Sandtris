#include "GamePlay.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "SaveData.hpp"
#include "TetrisEvent.hpp"
#include "constant.hpp"
#include "scene_transitions.hpp"
GamePlay::GamePlay(Game &game) : Scene(game) {
  game = &game;
  grid = Grid(game);

  score_font =
      Font(base_path + "assets/fonts/sandtris pixel.ttf", FONT_SIZE);
  score_surf = score_font.render("0", 0, "white");
  score_rect = score_surf.getRect();
  score_rect.setCenter(score_display_center);

  next_display_color = grid.next.color;
  flow1 = next_color_display_rect.inflate(0, 5);
  flow2 = flow1.move(0, next_color_display_rect.getHeight());
  color_flow1 = "none";
  color_flow2 = "none";

  next_shape_surf = Surface(next_shape_display_rect.getWidth(),
                            next_shape_display_rect.getHeight());
  redraw_next_shape();
  change_shape = Animation(game, 120);
  change_shape.load(base_path + "assets/animations/change_next_shape/");
  Surface tmp = Surface(next_shape_display_area.getWidth(),
                        next_shape_display_area.getHeight());
  tmp.fill("none");
  change_shape.set_default(tmp);

  count_down = Animation(game, 1);
  count_down.load(base_path + "assets/animations/count_down/");
  tmp = Surface(count_down_display_rect.getWidth(),
                count_down_display_rect.getHeight());
  tmp.fill("none");
  count_down.set_default(tmp);
  count_down.play();

  sdlgame::music::load(base_path +
                       "assets/audio/music/tetris_theme_loop_instrument.mp3");
  sdlgame::music::play(-1, 2000);

  pause_button = PauseButton(game);
  pause_button.rect.setTopRight(RESOLUTION_WIDTH, 0);

  gameover = 0;
  blipcount = 100;
  pausing = 0;
}
void GamePlay::load_grid(Grid grid) { grid = grid; }
void GamePlay::redraw_next_shape() {
  next_shape_surf.fill(Color());
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (grid.next.mask >> (15 - i * 4 - j) & 1)
        sdlgame::draw::rect(
            next_shape_surf, Color("white"),
            Rect(Vector2(6 * j, 6 * i) + (grid.next.type != 'I' and
                                                  grid.next.type != 'O'
                                              ? Vector2(4, 1)
                                              : Vector2()),
                 6, 6));
}
void GamePlay::handle_event(sdlgame::event::Event &event) {
  if (!count_down.playing) {
    grid.handle_event(event);
    pause_button.handle_event(event);
  }
  if (event.type == SCORING) {
    score_surf =
        score_font.render(std::to_string(grid.get_score()), 0, "white");
    score_rect = score_surf.getRect();
    score_rect.setCenter(score_display_center);
    if (get_personal_best() < grid.get_score())
      set_personal_best(grid.get_score());
  } else if (event.type == MERGING) {
    next_display_color = grid.next.color;
    redraw_next_shape();
    change_shape.play();
  } else if (event.type == GAMEOVER) {
    sdlgame::music::stop();
    delete_grid_data();
    gameover = 1;
  } else if (event.type == BUTTON_CLICK) {
    sdlgame::music::pause();
    pausing = 1;
    save_grid_data(grid);
  } else if (event.type == sdlgame::KEYDOWN) {
    if ((event["key"] == sdlgame::K_p or event["key"] == sdlgame::K_ESCAPE) and
        !game->in_transitioning() and !game->out_transitioning() and
        !gameover) {
      pause_button.on_click();
      sdlgame::music::pause();
      pausing = 1;
      save_grid_data(grid);
    }
  }
}
void GamePlay::update() {
  if (pausing and is_working() and
      !(game->out_transitioning() or game->in_transitioning())) {
    pausing = 0;
    count_down.reset();
    count_down.play();
  }
  if (!gameover) {
    if (!count_down.playing and !pausing) {
      sdlgame::music::resume();
      grid.update();
      double delta_y = -flow_speed * game->clock.delta_time().count();
      flow1.move_ip(0, delta_y);
      flow2.move_ip(0, delta_y);
      if (flow1.getBottom() - 1 <= next_color_display_rect.getTop()) {
        flow1.setTop(flow2.getBottom());
        color_flow1 =
            SandShiftColor.at(static_cast<uint8_t>(next_display_color));
      }
      if (flow2.getBottom() - 1 <= next_color_display_rect.getTop()) {
        flow2.setTop(flow1.getBottom());
        color_flow2 =
            SandShiftColor.at(static_cast<uint8_t>(next_display_color));
      }
      change_shape.update();
    } else {
      if (count_down.frame_change) {
        if (count_down.frame_id != 4)
          sdlgame::event::post(COUNT_DOWN);
        else
          sdlgame::event::post(COUNT_DOWN_START);
      }
      count_down.update();
    }
    bg_offset.x -=
        gameplay_bg_speed * game->clock.delta_time().count();
    bg_offset.y -=
        gameplay_bg_speed * game->clock.delta_time().count();
    if (bg_offset.x <= -8)
      bg_offset = Vector2();
    pause_button.update();
  } else {
    blipcount--;
  }
}
void GamePlay::draw() {
  game->window.blit(game->images.gameplay_background, bg_offset);

  sdlgame::draw::rect(game->window, color_flow1,
                      flow1.overlap(next_color_display_rect));
  sdlgame::draw::rect(game->window, color_flow2,
                      flow2.overlap(next_color_display_rect));

  game->window.blit(game->images.game_frame, Vector2());

  game->window.blit(next_shape_surf,
                          next_shape_display_rect.getTopLeft());

  game->window.blit((*change_shape.image),
                          next_shape_display_area.getTopLeft());
  if (!(blipcount / 10 & 1) and blipcount >= 0)
    grid.draw();

  if (count_down.playing)
    game->window.blit((*count_down.image),
                            count_down_display_rect.getTopLeft());

  if (blipcount == -1) {
    auto out = std::make_unique<OutSwipeDown>();
    auto in = std::make_unique<InSwipeDown>();
    std::unique_ptr<Scene> next =
        std::make_unique<GameOver>(*game, grid.get_score());
    game->pop_scene(std::move(out), std::move(next), std::move(in));
  }

  game->window.blit((*pause_button.image),
                          pause_button.rect.getTopLeft());
  game->window.blit(score_surf, score_rect.getTopLeft());
}

GamePlay::~GamePlay() {
  // sdlgame::music::stop();
}