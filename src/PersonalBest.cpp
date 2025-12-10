#include "PersonalBest.hpp"
#include "SaveData.hpp"
#include "constant.hpp"
PersonalBest::PersonalBest(Game &game) : Scene(game)
{
    back_button = BackButton(game);
    back_button.rect.setTopLeft(bb_pos);

    pb_font = Font(font_path,FONT_SIZE);
    score = get_personal_best();
    pb_surf = pb_font.render(to_string(score),0,"white");
    pb_rect = pb_surf.getRect();
    pb_rect.setCenter(pb_center);
}

void PersonalBest::update()
{
    back_button.update();
}

void PersonalBest::draw()
{
    this->game->window.blit(this->game->images.pb_background,Vector2());
    this->game->window.blit(this->pb_surf,pb_rect.getTopLeft());
    this->game->window.blit(this->back_button.image,bb_pos);
}

void PersonalBest::handle_event(Event &event)
{
    back_button.handle_event(event);
}