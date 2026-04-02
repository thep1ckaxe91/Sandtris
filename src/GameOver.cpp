#include "GameOver.hpp"
#include "constant.hpp"
#include "SaveData.hpp"
#include "Scene.hpp"
GameOver::GameOver(Game &game, int new_score) : Scene(game)
{
    menu = MenuButton(game);
    menu.rect = (*menu.image).getRect();
    menu.rect.setTopLeft(menu_button_pos);

    retry = RetryButton(game);
    retry.rect = (*retry.image).getRect();
    retry.rect.setTopLeft(retry_button_pos);

    score_font = Font(font_path, FONT_SIZE);

    new_score = new_score;
    pb = get_personal_best();

    if (new_score > pb)
    {
        set_personal_best(new_score);
        pb_surf = score_font.render("NEW PB !", 0, "white");
    }
    else
        pb_surf = score_font.render(std::to_string(pb), 0, "white");

    new_score_surf = score_font.render(std::to_string(new_score), 0, "white");
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
    game->window.blit(game->images.gameover_screen, Vector2());
    game->window.blit((*menu.image), menu.rect.getTopLeft());
    game->window.blit((*retry.image), retry.rect.getTopLeft());

    game->window.blit(new_score_surf, new_score_rect.getTopLeft());
    game->window.blit(pb_surf, pb_rect.getTopLeft());
}