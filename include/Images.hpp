#pragma once
#ifndef IMAGES_HPP
#define IMAGES_HPP
#include "engine.hpp"
#include <memory>

class Images {
public:
  std::shared_ptr<const sdlgame::surface::Surface> start_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> start_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> start_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> credit_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> credit_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> credit_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> quit_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> quit_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> quit_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> back_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> back_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> back_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> menu_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> menu_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> menu_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> retry_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> retry_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> retry_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> pb_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> pb_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> pb_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> htp_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> htp_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> htp_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> pause_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> pause_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> pause_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> option_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> option_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> option_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> resume_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface> resume_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface> resume_button_click;

  std::shared_ptr<const sdlgame::surface::Surface> gameplay_background;
  std::shared_ptr<const sdlgame::surface::Surface> mainmenu_background;
  std::shared_ptr<const sdlgame::surface::Surface> credit_image;
  std::shared_ptr<const sdlgame::surface::Surface> game_frame;
  std::shared_ptr<const sdlgame::surface::Surface> instruction_image;
  std::shared_ptr<const sdlgame::surface::Surface> pb_background;
  std::shared_ptr<const sdlgame::surface::Surface> pause_background;
  std::shared_ptr<const sdlgame::surface::Surface> gameover_screen;

  Images();
  void load();
};

#endif
