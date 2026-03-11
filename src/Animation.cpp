#include "Animation.hpp"
namespace fs = std::filesystem;

Animation::Animation(Game &game, int frame_rate, bool loop)
{
    this->frame_rate = frame_rate;
    this->loop = loop;
    this->playing = 0;
    this->frame_id = 0;
    this->game = &game;
}
Animation::Animation() = default;
/**
 * @brief load the animation's images in folder 'path'
 *
 * @param path the path to the folder the contain only images of the animation
 */
void Animation::load(const fs::path& path)
{
    this->frames.clear();
    std::vector<fs::directory_entry> entries;
    for (const auto &entry : fs::directory_iterator(path))
    {
        entries.push_back(entry);
    }
    
    std::ranges::sort(entries); // sort by name for consistency

    for (const auto &entry : entries)
        frames.emplace_back(sdlgame::image::load(entry.path().string()));
    // TODO!: This bug need refactor, frames got reallocate every time the vector grows
    // which invalidate 
    

    if (!this->default_img.texture)
    {
        this->default_img = frames[0];
        this->image = &frames[0];
    }
}
void Animation::update()
{
    if (this->playing)
    {
        this->frame_change = 0;
        this->time_cnt += this->game->clock.delta_time().count();

        if (this->time_cnt >= 1.0 / this->frame_rate)
        {
            this->time_cnt -= 1.0 / this->frame_rate;
            if (frame_id >= frames.size())
            {
                frame_id = 0;
                if (!(this->playing = this->loop))
                {
                    this->image = &this->default_img;
                    playing = 0;
                    return;
                }
            }
            this->image = &this->frames[frame_id];
            this->frame_id++;
            this->frame_change = 1;
        }
    }
}
void Animation::play()
{
    this->playing = 1;
}
void Animation::pause()
{
    playing = 0;
}
void Animation::reset()
{
    frame_id = 0;
}
void Animation::set_default(Surface oth)
{
    this->default_img = std::move(oth);
    this->image = &this->default_img;
}