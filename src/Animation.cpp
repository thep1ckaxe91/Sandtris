#include "Animation.hpp"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <memory>
namespace fs = std::filesystem;

Animation::Animation(Game &game, uint32_t frame_rate, bool loop)
    : game(&game), m_frame_rate(frame_rate), m_loop(loop) {}

/**
 * @brief load the animation's images in folder 'path'
 *
 * @param path the path to the folder the contain only images of the animation
 */
void Animation::load(const fs::path &path) {
  assert(fs::is_directory(path));
  // FIXME: NOW there's segfault caused by a blit call by the first animation of the splash screen
  // must check with gdb to see what 
  frames.clear();
  std::vector<fs::directory_entry> entries;
  for (const auto &entry : fs::directory_iterator(path)) {
    entries.push_back(entry);
  }

  assert(!entries.empty());

  frames.reserve(entries.size());
  std::ranges::sort(entries); // sort by name for consistency

  for (const auto &entry : entries) {
    frames.emplace_back(sdlgame::image::load(entry.path()));
  }

  if (!default_img || !default_img->getTexture()) {
    default_img = frames[0];
  }
  if (!m_image || !m_image->getTexture()) {
    m_image = default_img;
  }
}
void Animation::update() {
  if (m_playing) {
    m_frame_changed = 0;
    m_time_count += game->m_clock.delta_time().count();

    if (m_time_count >= 1.0 / m_frame_rate) {
      m_time_count -= 1.0 / m_frame_rate;
      if (m_frame_id >= frames.size()) {
        m_frame_id = 0;
        if (!(m_playing = m_loop)) {
          m_image = default_img;
          m_playing = 0;
          return;
        }
      }
      m_image = frames[m_frame_id];
      m_frame_id++;
      m_frame_changed = 1;
    }
  }
}
void Animation::play() { m_playing = 1; }
void Animation::pause() { m_playing = 0; }
void Animation::reset() { m_frame_id = 0; }
void Animation::set_default_image(const std::shared_ptr<const Surface> &oth) {
  default_img = oth;
  m_image = default_img;
}

const std::shared_ptr<const Surface> &Animation::get_default_image() const {
  return default_img;
}

bool Animation::is_playing() const { return m_playing; }
bool Animation::is_looped() const { return m_loop; }

size_t Animation::get_frame_index() const { return m_frame_id; }

/**
@return `true` if in that frame, the animation's frame has changed
  */
bool Animation::frame_changed() const { return m_frame_changed; }
uint32_t Animation::get_frame_rate() const { return m_frame_rate; };
void Animation::set_frame_rate(uint32_t frame_rate) {
  m_frame_rate = frame_rate;
};

std::span<const std::shared_ptr<const Surface>> Animation::get_frames() const {
  return frames;
}
