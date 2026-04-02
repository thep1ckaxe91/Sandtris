#include "HowToPlay.hpp"
#include "constant.hpp"

HowToPlay::HowToPlay(Game &game) : Scene(game)
{
    back_button = BackButton(game);
    back_button.rect.setTopLeft(bb_pos);
    height_pos = 0;
}

void HowToPlay::handle_event(Event &event)
{
    back_button.handle_event(event);
    if (event.type == sdlgame::MOUSEWHEEL)
    {
        height_pos += event["y"] * 4;
        height_pos = sdlgame::math::clamp(
            height_pos,
            -145,
            0);
        // cout << height_pos<<" "<<event["y"]  << endl;
    }
}
void HowToPlay::update()
{
    back_button.update();
}

void HowToPlay::draw()
{
    game->window.blit(game->images.instruction_image, Vector2(0, height_pos));
    game->window.blit((*back_button.image), bb_pos);
}
