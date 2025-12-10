#include "Credit.hpp"
#include "constant.hpp"

Credit::Credit(Game &game) : Scene(game)
{
    back_button = BackButton(game);
    back_button.rect.setTopLeft(this->bb_pos);
}

void Credit::handle_event(Event &event)
{
    back_button.handle_event(event);
}
void Credit::update()
{
    back_button.update();
}

void Credit::draw()
{
    this->game->window.blit(this->game->images.credit_image,Vector2());
    this->game->window.blit(this->back_button.image,bb_pos);
}
