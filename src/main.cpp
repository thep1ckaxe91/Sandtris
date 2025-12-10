// #define _CRTDBG_MAP_ALLOC
#include "engine/engine.hpp"
#include "splash_screens.hpp"
#include "scene_transitions.hpp"
#include "constant.hpp"
#include "engine/gpu_optimize.hpp"
#include "TetrisEvent.hpp"
#include "Grid.hpp"
#include "crtdbg.h"
#include "flags.hpp"
#include "SaveData.hpp"
using namespace std;
// If global declare is bad, i make MY OWN global declare >:)
class Sandtris : public Game
{
public:
    bool gameactive = 1;
    bool played = 0;
    Sandtris() : Game()
    {
        this->window_object = sdlgame::display::set_mode(
            RESOLUTION_WIDTH, RESOLUTION_HEIGHT,
            0
                // |sdlgame::MAXIMIZED
                | sdlgame::RESIZABLE);
        this->window = Surface(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
        sdlgame::display::get_window_size();

        auto res = load_window_info();
        if (res.second.first == 0)
            sdlgame::display::fullscreen_desktop();
        else
        {
            sdlgame::display::set_window_size(res.second.first, res.second.second);
            sdlgame::display::set_window_pos(res.first.first, res.first.second);
        }
        audio_manager = AudioManager();
        images = Images();
        images.load();
        sdlgame::display::set_caption("Sandtris - Made by thep1ckaxe");
        sdlgame::display::set_icon((base_path + "data/image/icon/icon.png").c_str());
#ifdef MULTITHREADING
        grid_mem_init();
#endif
        // cout<<this->images.start_button_idle.texture<<" "<<this->images.start_button_hover.texture<<" "<<this->images.start_button_click.texture<<endl;
        // exit(0);
    }
    void update()
    {
        if (!scene_list.empty())
            if (scene_list.back())
            {
                scene_list.back()->update();
            }
        if (this->out)
        {
            if (!played)
            {
                played = 1;
            }
            out->update(clock.delta_time());
            if (out->isDone)
            {
                delete out;
                out = nullptr;
                played = 0;
            }
        }
        else if (this->in)
        {
            if (this->next)
            {
                if (this->command == POP)
                {
                    this->command = NONE;
                    delete scene_list.back();
                    scene_list.pop_back();
                }
                else if (this->command == CLEAR)
                {
                    this->command = NONE;
                    while (!scene_list.empty())
                    {
                        delete scene_list.back();
                        scene_list.pop_back();
                    }
                }
                scene_list.push_back(this->next);
                this->next = nullptr;
            }
            else if (this->command == REMOVE)
            {
                this->command = NONE;
                delete scene_list[scene_list.size() - 1];
                scene_list.pop_back();
            }
            in->update(clock.delta_time());
            if (in->isDone)
            {
                delete in;
                in = nullptr;
            }
        }
        audio_manager.update();
    }
    void draw()
    {
        window.fill(Color(0, 0, 0));
        if (!scene_list.empty())
            if (scene_list.back())
            {
                scene_list.back()->draw();
            }
        window_object.blit(this->window, this->window_draw_offset);
        if (this->out)
        {
            out->draw();
        }
        else if (this->in)
        {
            in->draw();
        }
    }
    void run()
    {
        Animation studiosc(*this, 10, 1);
        studiosc.load(base_path + "data/animations/splash/studio/");
        studiosc.play();
        InFade *in = new InFade();
        StudioSC *next = new StudioSC(*this, studiosc, 8);
        this->add_scene(NULL, next, in);
        while (true)
        {
            clock.tick(MAXFPS);
            for (auto &event : sdlgame::event::get())
            {
                if (event.type == sdlgame::QUIT or (event.type == sdlgame::WINDOWEVENT and event["event"] == sdlgame::WINDOWCLOSE))
                {
                    // game_ended = 1;
                    sdlgame::quit();
                    exit(0);
                }
                else if (event.type == sdlgame::WINDOWEVENT)
                {
                    if (event["event"] == sdlgame::WINDOWFOCUSGAINED or event["event"] == sdlgame::WINDOWSHOWN)
                    {
                        gameactive = 1;
                        // cout << "focus gain" << endl;
                    }
                    else if (event["event"] == sdlgame::WINDOWFOCUSLOST)
                    {
                        gameactive = 0;
                    }
                    else if (event["event"] == sdlgame::WINDOWRESIZED or event["event"] == sdlgame::WINDOWSIZECHANGED)
                    {
                        Vector2 res = sdlgame::display::get_window_size();
                        if (sdlgame::display::is_fullscreen())
                        {
                            auto pos = sdlgame::display::get_window_pos();
                            save_window_info(pos.first, pos.second, 0, 0);
                        }
                        else
                        {
                            auto pos = sdlgame::display::get_window_pos();
                            save_window_info(pos.first, pos.second, int(res.x), int(res.y));
                        }
                    }
                    else if (event["event"] == sdlgame::WINDOWMOVED)
                    {
                        Vector2 res = sdlgame::display::get_window_size();
                        auto pos = sdlgame::display::get_window_pos();
                        save_window_info(pos.first, pos.second, int(res.x), int(res.y));
                    }
                }
                if (gameactive)
                {
                    if (!scene_list.empty())
                        scene_list.back()->handle_event(event);
                    audio_manager.handle_event(event);
                }
            }
            if (gameactive)
            {
                update();
                draw();
                sdlgame::display::flip();
                // sdlgame::display::set_caption((to_string(clock.get_fps())).c_str());
            }
        }
    }
};
int main(int argc, char **argv)
{
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    sdlgame::init();
    sdlgame::mixer::init();
    sdlgame::mixer::set_num_channels(16);
    Sandtris game;
    game.run();
    return 0;
}
/**
 *
 */