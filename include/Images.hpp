#pragma once
#include <SDL_render.h>
#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <sdlgame/surface.hpp>

class Images {
public:
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> start_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> start_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> start_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> credit_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> credit_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> credit_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> quit_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> quit_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> quit_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> back_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> back_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> back_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> menu_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> menu_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> menu_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> retry_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> retry_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> retry_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pb_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pb_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pb_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> htp_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> htp_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> htp_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pause_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pause_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pause_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> option_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> option_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> option_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> resume_button_idle;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> resume_button_hover;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> resume_button_click;

  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> gameplay_background;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> mainmenu_background;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> credit_image;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> game_frame;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> instruction_image;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pb_background;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> pause_background;
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> gameover_screen;

  Images();
  void load();
};

#endif
