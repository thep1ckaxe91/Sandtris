#pragma once
#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include "CreditButton.hpp"
#include "HTPButton.hpp"
#include "OptionButton.hpp"
#include "PBButton.hpp"
#include "QuitButton.hpp"
#include "ResumeButton.hpp"
#include "Scene.hpp"
#include "StartButton.hpp"
#include "engine.hpp"
#include <memory>

class MainMenu : public Scene {
public:
  std::shared_ptr<StartButton> start_button;
  std::shared_ptr<QuitButton> quit_button;
  std::shared_ptr<CreditButton> credit_button;
  std::shared_ptr<PBButton> pb_button;
  std::shared_ptr<HTPButton> htp_button;
  std::shared_ptr<OptionButton> option_button;
  std::shared_ptr<ResumeButton> resume_button;

  bool can_resume;
  MainMenu(Game &game);
  void handle_event(const Event &event);
  void update();
  void draw();
  ~MainMenu();
};

#endif
