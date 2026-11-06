#include "GameOver.hpp"
#include "SaveData.hpp"
#include "Scene.hpp"
#include "constant.hpp"
#include <sdlgame/color.hpp>
#include <sdlgame/font.hpp>
#include <sdlgame/math.hpp>

using sdlgame::color::Color;
using sdlgame::math::Vector2;

GameOver::GameOver(Game &game_ref, int score)
    : Scene(game_ref), score_font(font_path, FONT_SIZE), new_score(score) {
  menu = std::make_shared<MenuButton>(game);
  menu->get_rect().setTopLeft(menu_button_pos);

  retry = std::make_shared<RetryButton>(game);
  retry->get_rect().setTopLeft(retry_button_pos);

  pb = get_personal_best();

  if (new_score > pb) {
    set_personal_best(new_score);
    pb_surf = score_font.render("NEW PB !", sdlgame::font::AntiAlias::SOLID,
                                Color{"white"});
  } else
    pb_surf = score_font.render(
        std::to_string(pb), sdlgame::font::AntiAlias::SOLID, Color{"white"});

  new_score_surf =
      score_font.render(std::to_string(new_score),
                        sdlgame::font::AntiAlias::SOLID, Color{"white"});
  new_score_rect = new_score_surf.get_rect();
  new_score_rect.setMidBottom(midbottom_newscore);
  pb_rect = pb_surf.get_rect();
  pb_rect.setMidBottom(midbottom_pb);
}

void GameOver::handle_event(const sdlgame::event::Event &event) {
  menu->handle_event(event);
  retry->handle_event(event);
}

void GameOver::update() {
  menu->update();
  retry->update();
}

void GameOver::draw() {
  game.m_window.blit(*game.images.gameover_screen, Vector2());
  game.m_window.blit(menu->get_image(), menu->get_rect().getTopLeft());
  game.m_window.blit(retry->get_image(), retry->get_rect().getTopLeft());

  game.m_window.blit(new_score_surf, new_score_rect.getTopLeft());
  game.m_window.blit(pb_surf, pb_rect.getTopLeft());
}
