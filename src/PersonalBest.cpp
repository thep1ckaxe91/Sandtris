#include "PersonalBest.hpp"
#include "SaveData.hpp"
#include "constant.hpp"
PersonalBest::PersonalBest(Game &game) : Scene(game)
{
    back_button = BackButton(game);
    back_button.rect.setTopLeft(bb_pos);

    pb_font = Font(font_path,FONT_SIZE);
    score = get_personal_best();
    pb_surf = pb_font.render(std::to_string(score),0,"white");
    pb_rect = pb_surf.get_rect();
    pb_rect.setCenter(pb_center);
}

void PersonalBest::update()
{
    back_button.update();
}

void PersonalBest::draw()
{
    game->m_window.blit(game->m_images.pb_background,Vector2());
    game->m_window.blit(pb_surf,pb_rect.getTopLeft());
    game->m_window.blit(*back_button.image,bb_pos);
}

void PersonalBest::handle_event(const Event &event)
{
    back_button.handle_event(event);
}