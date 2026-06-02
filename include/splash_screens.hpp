#pragma once
#ifndef SPLASH_SCREENS_HPP
#define SPLASH_SCREENS_HPP

#include "SplashScreen.hpp"
#include <memory>

class StudioSC : public SplashScreen {
public:
  StudioSC(Game &gameInstance, std::shared_ptr<Animation> anim, double duration = 3);
  void handle_event(const Event &event) override;
  void update() override;
  void on_finish() override;
};

class SDLSC : public SplashScreen {
public:
  SDLSC(Game &gameInstance, std::shared_ptr<Animation> anim, double duration = 2);
  void handle_event(const Event &event) override;
  void update() override;
  void on_finish() override;
};

#endif
