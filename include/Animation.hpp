#include "engine.hpp"
#include "Game.hpp"
#include <filesystem>
namespace fs = std::filesystem;

class Animation : public sdlgame::sprite::Sprite
{
protected:
    Surface default_img;
    double time_cnt = 0;
public:
    std::vector<Surface> frames;
    size_t frame_id;
    Game *game;
    int frame_rate;
    bool frame_change=0;
    bool loop;
    bool playing;
    /**
     * @brief init an animation object
     * @param path path to the folder that only have file for the 
     * 
     */
    Animation(Game &game, int frame_rate=60, bool loop=0);
    Animation();
    /**
     * @brief load the animation's images in folder 'path'
     * 
     * @param path the path to the folder the contain only images of the animation
     */
    void load(const fs::path& path);
    void play();
    void update()override;
    void pause();
    void reset();
    void set_default(const Surface oth);
};