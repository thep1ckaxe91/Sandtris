#pragma once
#include "Game.hpp"
#include <SDL_render.h>
#include <filesystem>
#include <sdlgame/sprite.hpp>
#include <sdlgame/surface.hpp>

namespace fs = std::filesystem;

class Animation : public sdlgame::sprite::Sprite {
protected:
  std::shared_ptr<const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>>
      default_img;
  double m_time_count = 0;
  std::vector<std::shared_ptr<
      const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>>>
      frames;
  Game *game;
  size_t m_frame_id;
  uint32_t m_frame_rate;
  bool m_frame_changed = false;
  bool m_loop;
  bool m_playing = false;

public:
  /**
   * @brief init an animation object
   */
  Animation(Game &game, uint32_t frame_rate = 60, bool loop = false);

  /**
   * @brief load the animation's images in folder 'path'
   *
   * @param path the path to the folder the contain only images of the animation
   */
  void load(const fs::path &path);
  void play();
  void update() override;
  void pause();
  void reset();
  void set_default_image(
      const std::shared_ptr<
          const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> &oth);
  const std::shared_ptr<
      const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>> &
  get_default_image() const;
  bool is_playing() const;
  bool is_looped() const;
  size_t get_frame_index() const;

  /**
  @return `true` if in that frame, the animation's frame has changed
   */
  bool frame_changed() const;
  uint32_t get_frame_rate() const;
  void set_frame_rate(uint32_t frame_rate);

  std::span<const std::shared_ptr<
      const sdlgame::surface::Surface<SDL_TEXTUREACCESS_STATIC>>>
  get_frames() const;
};