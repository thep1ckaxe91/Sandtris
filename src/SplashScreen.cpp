#include "SplashScreen.hpp"

SplashScreen::SplashScreen(Game &game, double time, Animation &anim ) : Scene(game)
{
    time = time;
    splash = anim;
    done = 0;
}
SplashScreen::SplashScreen()=default;
void SplashScreen::play()
{
    splash.play();
}
void SplashScreen::handle_event(Event &event)
{
    if(event.type == sdlgame::MOUSEBUTTONDOWN)
    {
        on_finish();
        done = 1;
    }
}
void SplashScreen::update()
{
    if(splash.playing)
    {
        splash.update();
        // cout << game->clock.delta_time().count() << endl;
        time -= game->clock.delta_time().count();
        // cout << time << endl;
        if(time <= 0){
            splash.playing=0;
        }
    }
    else{
        if(!done) on_finish();
        done=1;
    }
}
void SplashScreen::draw()
{
    game->window.blit(*splash.image,Vector2());
}
SplashScreen::~SplashScreen() = default;