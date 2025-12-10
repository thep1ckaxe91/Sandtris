#include "splash_screens.hpp"
#include "scene_transitions.hpp"
#include "MainMenu.hpp"

SDLSC::SDLSC(Game &game,  Animation anim,double time) : SplashScreen(game,time,anim)
{
    this->game=&game;
}
void SDLSC::handle_event(Event &event)
{  
    SplashScreen::handle_event(event);
}
void SDLSC::update()
{
    SplashScreen::update();
}
void SDLSC::on_finish()
{
    OutFade *out = new OutFade(1);
    InFade *in = new InFade(1);
    MainMenu *next = new MainMenu(*game);
    this->game->pop_scene(out,next,in);
}

StudioSC::StudioSC(Game &game,  Animation anim,double time) : SplashScreen(game,time,anim)
{
    this->game = &game;
    this->game->audio_manager.sfx.soft_wind_blow.play();
}
void StudioSC::handle_event(Event &event)
{  
    SplashScreen::handle_event(event);
}
void StudioSC::update()
{
    SplashScreen::update();
}
void StudioSC::on_finish()
{
    Animation sdlsc(*game,30,1);
    sdlsc.load(base_path + "data/animations/splash/sdl/");
    sdlsc.set_default(sdlsc.frames.back());
    sdlsc.play();
    OutFade *out = new OutFade(1);
    InFade *in = new InFade(1);
    SDLSC *next = new SDLSC(*game,sdlsc,5);
    this->game->pop_scene(out,next,in);
    this->game->audio_manager.sfx.soft_wind_blow.fadeout(1000);
}
