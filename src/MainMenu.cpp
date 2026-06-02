#include "MainMenu.hpp"
#include "SaveData.hpp"
#include "constant.hpp"
#include <iostream>

MainMenu::MainMenu(Game &game_ref) : Scene(game_ref) {
  if (have_grid_data()) {
    resume_button = std::make_shared<ResumeButton>(game);
    resume_button->get_rect().setTopLeft(8, RESOLUTION_HEIGHT - 8 * 4 - 16 * 4);
    can_resume = true;
  } else {
    can_resume = false;
  }

  start_button = std::make_shared<StartButton>(game);
  start_button->get_rect().setTopLeft(8, RESOLUTION_HEIGHT - 8 * 3 - 16 * 3);
  credit_button = std::make_shared<CreditButton>(game);
  credit_button->get_rect().setTopLeft(8, RESOLUTION_HEIGHT - 8 * 2 - 16 * 2);
  quit_button = std::make_shared<QuitButton>(game);
  quit_button->get_rect().setTopLeft(8, RESOLUTION_HEIGHT - 8 - 16);

  pb_button = std::make_shared<PBButton>(game);
  pb_button->get_rect().setTopLeft(119 - 32 - 2, 104);
  htp_button = std::make_shared<HTPButton>(game);
  htp_button->get_rect().setTopLeft(119, 104);
  option_button = std::make_shared<OptionButton>(game);
  option_button->get_rect().setTopLeft(119 - 64 - 4, 104);

  sdlgame::music::load(base_path / "assets" / "audio" / "music" /"mainmenu_theme_loop.mp3");
  sdlgame::music::play(-1, 1000);
}

void MainMenu::handle_event(const Event &event) {
  start_button->handle_event(event);
  quit_button->handle_event(event);
  credit_button->handle_event(event);
  pb_button->handle_event(event);
  htp_button->handle_event(event);
  option_button->handle_event(event);
  if (can_resume)
    resume_button->handle_event(event);
}

void MainMenu::update() {
  start_button->update();
  quit_button->update();
  credit_button->update();
  pb_button->update();
  htp_button->update();
  option_button->update();
  if (can_resume)
    resume_button->update();
}

void MainMenu::draw() {
  game.m_window.blit(*game.images.mainmenu_background, Vector2());
  game.m_window.blit(start_button->get_image(),
                     start_button->get_rect().getTopLeft());
  game.m_window.blit(credit_button->get_image(),
                     credit_button->get_rect().getTopLeft());
  game.m_window.blit(quit_button->get_image(),
                     quit_button->get_rect().getTopLeft());
  game.m_window.blit(pb_button->get_image(),
                     pb_button->get_rect().getTopLeft());
  game.m_window.blit(htp_button->get_image(),
                     htp_button->get_rect().getTopLeft());
  game.m_window.blit(option_button->get_image(),
                     option_button->get_rect().getTopLeft());
  if (can_resume)
    game.m_window.blit(resume_button->get_image(),
                       resume_button->get_rect().getTopLeft());
}

MainMenu::~MainMenu() {}
