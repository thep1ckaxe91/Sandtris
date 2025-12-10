#include "MainMenu.hpp"
#include "constant.hpp"
#include "SaveData.hpp"
MainMenu::MainMenu(Game &game) : Scene(game){

    if(have_grid_data())
    {
        this->resume_button = ResumeButton(game);
        this->resume_button.rect.setTopLeft(8,RESOLUTION_HEIGHT-8*4-16*4);
        this->can_resume = 1;
    }
    else this->can_resume = 0;

    this->start_button = StartButton(game);
    this->start_button.rect.setTopLeft(8,RESOLUTION_HEIGHT-8*3-16*3);
    this->credit_button = CreditButton(game);
    this->credit_button.rect.setTopLeft(8,RESOLUTION_HEIGHT-8*2-16*2);
    this->quit_button = QuitButton(game);
    this->quit_button.rect.setTopLeft(8,RESOLUTION_HEIGHT-8-16);

    this->pb_button = PBButton(game);
    this->pb_button.rect.setTopLeft(119-32-2,104);
    this->htp_button = HTPButton(game);
    this->htp_button.rect.setTopLeft(119,104);
    this->option_button = OptionButton(game);
    this->option_button.rect.setTopLeft(119-64-4,104);

    sdlgame::music::load(base_path + "data/audio/music/mainmenu_theme_loop.mp3");
    sdlgame::music::play(-1,1000);
}
void MainMenu::handle_event(Event &event)
{
    this->start_button.handle_event(event);
    this->quit_button.handle_event(event);
    this->credit_button.handle_event(event);
    this->pb_button.handle_event(event);
    this->htp_button.handle_event(event);
    this->option_button.handle_event(event);
    if(this->can_resume) this->resume_button.handle_event(event);
}
void MainMenu::update(){
    this->start_button.update();
    this->quit_button.update();
    this->credit_button.update();
    this->pb_button.update();
    this->htp_button.update();
    this->option_button.update();
    if(this->can_resume) this->resume_button.update();
}
void MainMenu::draw(){
    this->game->window.blit(this->game->images.mainmenu_background,sdlgame::math::Vector2());
    this->game->window.blit(this->start_button.image,this->start_button.rect.getTopLeft());
    this->game->window.blit(this->credit_button.image,this->credit_button.rect.getTopLeft());
    this->game->window.blit(this->quit_button.image,this->quit_button.rect.getTopLeft());
    this->game->window.blit(this->pb_button.image,pb_button.rect.getTopLeft());
    this->game->window.blit(this->htp_button.image, htp_button.rect.getTopLeft());   
    this->game->window.blit(this->option_button.image, option_button.rect.getTopLeft());
    if(this->can_resume)
        this->game->window.blit(this->resume_button.image,resume_button.rect.getTopLeft());
}
MainMenu::~MainMenu()
{
    
}