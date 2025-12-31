#include"Pause.hpp"
Pause::Pause(Game &game) : Scene(game)
{
    message_font = Font(font_path,FONT_SIZE);
    message_surf = message_font.render("Progress will be save",0,"white");
    message_rect = message_surf.getRect();
    message_rect.setCenter(RESOLUTION_WIDTH/2,RESOLUTION_HEIGHT-message_rect.getHeight()/2 - 2);
    menu_button = MenuButton(game);
    menu_button.rect.setCenter(55,64);
    retry_button = RetryButton(game);
    retry_button.rect.setCenter(55,64+16+2);
    back_button = BackButton(game);
    back_button.rect.setCenter(55,64+4+32);
    option_button = OptionButton(game);
    option_button.rect.setCenter(102,68);
}

Pause::Pause() = default;

void Pause::render_message(string new_message)
{
    message_surf = message_font.render(new_message,0,"white");
    message_rect = message_surf.getRect();
    message_rect.setCenter(RESOLUTION_WIDTH/2,RESOLUTION_HEIGHT-message_rect.getHeight()/2 - 2);
}
void Pause::display_message()
{
    this->game->window.blit(this->message_surf,message_rect.getTopLeft());
}
void Pause::update()
{
    menu_button.update();
    if(menu_button.hovering and !menu_button.prev_hovered)
        render_message("Progress will be save");
    
    option_button.update();
    retry_button.update();
    back_button.update();        
}

void Pause::handle_event(Event &event)
{
    menu_button.handle_event(event);
    option_button.handle_event(event);
    retry_button.handle_event(event);
    back_button.handle_event(event);    
}
void Pause::draw()
{
    this->game->window.blit(this->game->images.pause_background,Vector2());
    this->game->window.blit(menu_button.image,menu_button.rect.getTopLeft());
    this->game->window.blit(option_button.image,option_button.rect.getTopLeft());
    this->game->window.blit(retry_button.image,retry_button.rect.getTopLeft());
    this->game->window.blit(back_button.image,back_button.rect.getTopLeft());
    if(menu_button.hovering) display_message();
}