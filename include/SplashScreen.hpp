#ifndef SPLASH_SCREEN_HPP
#define SPLASH_SCREEN_HPP
#include "Animation.hpp"
#include "Scene.hpp"

class SplashScreen : public Scene {
private:
public:
  std::shared_ptr<Animation> m_animation;
  double m_time;
  bool m_done = 0;
  /**
   * @brief Construct a new Splash Screen object
   *
   * @param game
   * @param time total time for splash screen from in transition start and out
   * transition end;
   */
  SplashScreen(Game &game, double time, const std::shared_ptr<Animation> &anim);
  void play();
  virtual void on_finish() = 0;
  virtual void handle_event(const Event &event);
  virtual void update();
  void draw();
  virtual ~SplashScreen();
};

#endif