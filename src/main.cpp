// #define _CRTDBG_MAP_ALLOC
#include "SaveData.hpp"
#include "SceneTransition.hpp"
#include "constant.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include "scene_transitions.hpp"
#include "splash_screens.hpp"
#include <SDL2/SDL_render.h>
#include <memory>
#include <print>
using Timer = sdlgame::time::Timer;
using TimerManager = sdlgame::time::TimerManager;

static void print_bench_stat() {
  for (auto &[name, stat] : TimerManager::instance().get_all()) {
    std::print("{} stats:\nTotal: {}\nMax: {}\nMin: {}\nAvg: {}\n", name,
               stat.total_time.count(), stat.max_time.count(),
               stat.min_time.count(), stat.avg_time().count());
  }
}

// If global declare is bad, i make MY OWN global declare >:)
class Sandtris : public Game {
public:
  bool gameactive = 1;
  bool played = 0;
  Sandtris() : Game() {
    window_object =
        sdlgame::display::set_mode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT,
                                   0 | sdlgame::MAXIMIZED | sdlgame::RESIZABLE);
    window = Surface(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    sdlgame::display::get_window_size(); // this is intended to assign win_surf
                                         // a value it suppose to be

    // comment this so that i get a free fps view at the caption
    // auto res = load_window_info();
    // if (res.second.first == 0)
    //     sdlgame::display::fullscreen_desktop();
    // else
    // {
    // sdlgame::display::set_window_size(res.second.first, res.second.second);
    // sdlgame::display::set_window_pos(res.first.first, res.first.second);
    // }
    audio_manager = AudioManager();
    images = Images();
    images.load();
    sdlgame::display::set_caption("Sandtris - Made by thep1ckaxe");
    sdlgame::display::set_icon(
        (base_path + "assets/image/icon/icon.png").c_str());

    // cout<<images.start_button_idle.texture<<"
    // "<<images.start_button_hover.texture<<"
    // "<<images.start_button_click.texture<<endl; exit(0);
  }
  void update() {
    Timer t("update");
    if (!scene_list.empty())
      if (scene_list.back()) {
        scene_list.back()->update();
      }
    if (out) {
      played = true;
      out->update(clock.delta_time().count());
      if (out->isDone) {
        out.reset();
        played = 0;
      }
    } else if (in) {
      if (next) {
        if (command == POP) {
          command = NONE;
          scene_list.pop_back();
        } else if (command == CLEAR) {
          command = NONE;
          while (!scene_list.empty()) {
            scene_list.pop_back();
          }
        }
        scene_list.emplace_back(std::move(next));
      } else if (command == REMOVE) {
        command = NONE;
        scene_list.pop_back();
      }
      in->update(clock.delta_time().count());
      if (in->isDone) {
        in.reset();
      }
    }
    audio_manager.update();
  }
  void draw() {
    Timer t("draw");
    window.fill(Color(0, 0, 0));
    if (!scene_list.empty())
      if (scene_list.back()) {
        scene_list.back()->draw();
      }
    window_object.blit(window, window_draw_offset);
    if (out) {
      out->draw();
    } else if (in) {
      in->draw();
    }
  }
  void run() {
    Animation studiosc(*this, 10, 1);
    studiosc.load(base_path + "assets/animations/splash/studio/");
    studiosc.play();
    auto in = std::make_unique<InFade>();
    std::unique_ptr<Scene> next = std::make_unique<StudioSC>(*this, studiosc, 8);
    add_scene(nullptr, std::move(next), std::move(in));
    bool running = true;
    while (running) {
      clock.tick(1e9);
      {
        Timer t("event");
        for (auto &event : sdlgame::event::get()) {
          if (event.type == sdlgame::QUIT or
              (event.type == sdlgame::WINDOWEVENT and
               event["event"] == sdlgame::WINDOWCLOSE)) {
            print_bench_stat();
            running = false;
            sdlgame::quit();
          } else if (event.type == sdlgame::WINDOWEVENT) {
            Vector2 res;
            switch (event["event"]) {
            case sdlgame::WINDOWFOCUSGAINED:
            case sdlgame::WINDOWSHOWN:
              gameactive = 1;
              break;
            case sdlgame::WINDOWFOCUSLOST:
              gameactive = 0;
              break;
            case sdlgame::WINDOWRESIZED:
            case sdlgame::WINDOWSIZECHANGED:
              res = sdlgame::display::get_window_size();
              if (sdlgame::display::is_fullscreen()) {
                auto pos = sdlgame::display::get_window_pos();
                save_window_info(pos.first, pos.second, 0, 0);
              } else {
                auto pos = sdlgame::display::get_window_pos();
                save_window_info(pos.first, pos.second, int(res.x), int(res.y));
              }
              break;

            case sdlgame::WINDOWMOVED:
              res = sdlgame::display::get_window_size();
              auto pos = sdlgame::display::get_window_pos();
              save_window_info(pos.first, pos.second, int(res.x), int(res.y));
              break;
            }
          }
          if (gameactive) [[likely]] {
            if (!scene_list.empty())
              scene_list.back()->handle_event(event);
            audio_manager.handle_event(event);
          }
        }
      }
      if (gameactive) [[likely]] {
        update();
        draw();
        sdlgame::display::flip();
        sdlgame::display::set_caption(
            (std::to_string(clock.get_fps())).c_str());
      }
    }
  }
};
int main(int argc, char **argv) {
  sdlgame::init();
  sdlgame::mixer::init();
  sdlgame::mixer::set_num_channels(16);
  Sandtris game;
  game.run();

  return 0;
}