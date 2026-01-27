#include "Animation.hpp"
#include <filesystem>
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
void Animation::load(std::string path)
{
    this->frames.clear();
    for (const auto &entry : fs::directory_iterator(path))
    {
        frames.push_back(sdlgame::image::load(entry.path().string()));
    }
    if (this->default_img.texture == 0)
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
            if (frame_id >= (int)frames.size())
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