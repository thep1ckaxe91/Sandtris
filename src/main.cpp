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

using namespace std::string_literals;

using Timer = sdlgame::time::Timer;
using TimerManager = sdlgame::time::TimerManager;

static void print_bench_stat() {
  for (auto &[name, stat] : TimerManager::instance().get_all()) {
    std::print("{} stats:\nTotal: {}\nMax: {}\nMin: {}\nAvg: {}\n", name,
               stat.total_time.count(), stat.max_time.count(),
               stat.min_time.count(), stat.avg_time().count());
  }
}

class Sandtris : public Game {
public:
  bool m_gameactive = true;
  bool played = false;
  Sandtris() : Game() {
    m_window_object =
        sdlgame::display::set_mode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT,
                                   0 | sdlgame::MAXIMIZED | sdlgame::RESIZABLE);
    m_window = Surface(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    sdlgame::display::get_window_size(); // TODO: this is intended to assign
                                         // proxy_surf a value it suppose to be,
                                         // but there should be a way to make
                                         // this unnecessary

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
        (base_path / "assets" / "image" / "icon" / "icon.png").c_str());

  }
  void update() override {
    Timer t("update");
    if (!m_scene_list.empty())
      if (m_scene_list.back()) {
        m_scene_list.back()->update();
      }

    // FIXME: This could be refactor to a state machine for readability and also
    // scalability

    if (m_out) {
      played = true;
      m_out->update(m_clock.delta_time().count());
      if (m_out->isDone) {
        m_out.reset();
        played = false;
      }
    } else if (m_in) {
      if (m_next) {
        if (m_command == SceneCommand::POP) {
          m_command = SceneCommand::NONE;
          m_scene_list.pop_back();
        } else if (m_command == SceneCommand::CLEAR) {
          m_command = SceneCommand::NONE;
          while (!m_scene_list.empty()) {
            m_scene_list.pop_back();
          }
        }
        m_scene_list.emplace_back(std::move(m_next));
      } else if (m_command == SceneCommand::REMOVE) {
        m_command = SceneCommand::NONE;
        m_scene_list.pop_back();
      }
      m_in->update(m_clock.delta_time().count());
      if (m_in->isDone) {
        m_in.reset();
      }
    }
    audio_manager.update();
  }
  void draw() override {
    Timer t("draw");
    m_window.fill(Color(0, 0, 0));
    m_window_object.fill(Color(0, 0, 0));
    if (!m_scene_list.empty())
      if (m_scene_list.back()) {
        m_scene_list.back()->draw();
      }
    m_window_object.blit(m_window, m_window_draw_offset);
    if (m_out) {
      m_out->draw();
    } else if (m_in) {
      m_in->draw();
    }
  }
  void run() override {
    auto studiosc_anim = std::make_shared<Animation>(*this, 10, true);
    studiosc_anim->load(base_path / "assets" / "animations" / "splash" / "studio");
    studiosc_anim->play();
    auto in = std::make_unique<InFade>();
    std::unique_ptr<Scene> next =
        std::make_unique<StudioSC>(*this, studiosc_anim, 8);
    add_scene(nullptr, std::move(next), std::move(in));
    bool running = true;
    while (running) {
      m_clock.tick(1e9);
      {
        Timer t("event");
        for (auto &event : sdlgame::event::get()) {
          if (event.type == sdlgame::QUIT or
              (event.type == sdlgame::WINDOWEVENT and
               event["event"] == sdlgame::WINDOWCLOSE)) {
            print_bench_stat();
            running = false;
            break;
          } else if (event.type == sdlgame::WINDOWEVENT) {
            Vector2 res;
            switch (event["event"]) {
            case sdlgame::WINDOWFOCUSGAINED:
            case sdlgame::WINDOWSHOWN:
              m_gameactive = true;
              break;
            case sdlgame::WINDOWFOCUSLOST:
              m_gameactive = false;
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
          if (m_gameactive) [[likely]] {
            if (!m_scene_list.empty())
              m_scene_list.back()->handle_event(event);
            audio_manager.handle_event(event);
          }
        }
      }
      if (m_gameactive) [[likely]] {
        update();
        draw();
        sdlgame::display::flip();
        sdlgame::display::set_caption(
            (std::to_string(m_clock.get_fps())).c_str());
      }
    }
  }
};
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  sdlgame::init();
  sdlgame::mixer::init();
  sdlgame::mixer::set_num_channels(16);
  Sandtris game;
  game.run();

  return 0;
}
