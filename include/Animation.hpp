#include "engine/engine.hpp"
#include "Game.hpp"
// #include "bits/stdc++.h"
class Animation : public sdlgame::sprite::Sprite
{
protected:
    Surface default_img;
    double time_cnt = 0;
public:
    std::vector<Surface> frames;
    int frame_id;
    bool frame_change=0;
    int frame_rate;
    bool loop;
    bool playing;
    Game *game;
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
    void load(std::string path);
    void play();
    void update()override;
    void pause();
    void reset();
    void set_default(const Surface oth);
};