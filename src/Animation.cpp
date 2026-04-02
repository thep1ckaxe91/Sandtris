#include "Animation.hpp"
namespace fs = std::filesystem;

Animation::Animation(Game &game, int frame_rate, bool loop) {
  frame_rate = frame_rate;
  loop = loop;
  playing = 0;
  frame_id = 0;
  game = &game;
}
Animation::Animation() = default;
/**
 * @brief load the animation's images in folder 'path'
 *
 * @param path the path to the folder the contain only images of the animation
 */
void Animation::load(const fs::path &path) {
  frames.clear();
  std::vector<fs::directory_entry> entries;
  for (const auto &entry : fs::directory_iterator(path)) {
    entries.push_back(entry);
  }
  frames.reserve(entries.size());
  std::ranges::sort(entries); // sort by name for consistency

  for (const auto &entry : entries) {
    frames.push_back(sdlgame::image::load(entry.path().string()));
  }

  if (!default_img.texture) {
    default_img = frames[0];
    image = &frames[0];
  }
}
void Animation::update() {
  if (playing) {
    frame_change = 0;
    time_cnt += game->clock.delta_time().count();

    if (time_cnt >= 1.0 / frame_rate) {
      time_cnt -= 1.0 / frame_rate;
      if (frame_id >= frames.size()) {
        frame_id = 0;
        if (!(playing = loop)) {
          image = &default_img;
          playing = 0;
          return;
        }
      }
      image = &frames[frame_id];
      frame_id++;
      frame_change = 1;
    }
  }
}
void Animation::play() { playing = 1; }
void Animation::pause() { playing = 0; }
void Animation::reset() { frame_id = 0; }
void Animation::set_default(Surface oth) {
  default_img = std::move(oth);
  image = &default_img;
}