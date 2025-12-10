#include "SplashScreen.hpp"

SplashScreen::SplashScreen(Game &game, double time, Animation &anim ) : Scene(game)
{
    this->time = time;
    this->splash = anim;
    this->done = 0;
}
SplashScreen::SplashScreen()=default;
void SplashScreen::play()
{
    this->splash.play();
}
void SplashScreen::handle_event(Event &event)
{
    if(event.type == sdlgame::MOUSEBUTTONDOWN)
    {
        this->on_finish();
        this->done = 1;
    }
}
void SplashScreen::update()
{
    if(this->splash.playing)
    {
        this->splash.update();
        // cout << this->game->clock.delta_time() << endl;
        this->time -= this->game->clock.delta_time();
        // cout << this->time << endl;
        if(this->time <= 0){
            this->splash.playing=0;
        }
    }
    else{
        if(!done) this->on_finish();
        done=1;
    }
}
void SplashScreen::draw()
{
    this->game->window.blit(this->splash.image,Vector2());
}
SplashScreen::~SplashScreen() = default;