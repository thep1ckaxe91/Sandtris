#include "GameOver.hpp"
#include "constant.hpp"
#include "SaveData.hpp"
#include "Scene.hpp"
GameOver::GameOver(Game &game, int new_score) : Scene(game)
{
    menu = MenuButton(game);
    menu.rect = menu.image.getRect();
    menu.rect.setTopLeft(menu_button_pos);

    retry = RetryButton(game);
    retry.rect = retry.image.getRect();
    retry.rect.setTopLeft(retry_button_pos);

    score_font = Font(font_path,FONT_SIZE);

    this->new_score = new_score;
    this->pb = get_personal_best();

    if(this->new_score>this->pb)
    {
        set_personal_best(new_score);
        pb_surf = score_font.render("NEW PB !",0,"white");
    }
    else
        pb_surf = score_font.render(to_string(this->pb),0,"white");

    new_score_surf = score_font.render(to_string(new_score),0,"white");
    new_score_rect = new_score_surf.getRect();
    new_score_rect.setMidBottom(midbottom_newscore);
    pb_rect = pb_surf.getRect();
    pb_rect.setMidBottom(midbottom_pb);

}

void GameOver::handle_event(Event &event)
{
    menu.handle_event(event); 
    retry.handle_event(event);
}

void GameOver::update()
{
    menu.update();
    retry.update();
}

void GameOver::draw()
{
    this->game->window.blit(this->game->images.gameover_screen,Vector2());
    this->game->window.blit(this->menu.image,menu.rect.getTopLeft());
    this->game->window.blit(this->retry.image,retry.rect.getTopLeft());

    this->game->window.blit(this->new_score_surf,new_score_rect.getTopLeft());
    this->game->window.blit(this->pb_surf,pb_rect.getTopLeft());
}