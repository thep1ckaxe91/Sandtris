#pragma once
#ifndef SPLASH_SCREEN_HPP
#define SPLASH_SCREEN_HPP
#include "Animation.hpp"
#include "Scene.hpp"
#include <memory>

class SplashScreen : public Scene {
public:
  std::shared_ptr<Animation> splash;
  double time;
  bool done;
  /**
   * @brief Construct a new Splash Screen object
   *
   * @param game
   * @param time total time for splash screen from in transition start and out
   * transition end;
   */
  SplashScreen(Game &gameInstance, double duration, std::shared_ptr<Animation> anim);
  void play();
  virtual void on_finish() = 0;
  void handle_event(const Event &event) override;
  void update() override;
  void draw() override;
  ~SplashScreen() override;
};

#endif
