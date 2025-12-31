#include "Option.hpp"
#include "SaveData.hpp"
Option::Option(Game &game) : Scene(game)
{
    sfx_slider = SFXVolumeSlider(game, Vector2(80, 32), this->game->audio_manager.get_sfx_volume(), 48, 1);
    music_slider = MusicVolumeSlider(game, Vector2(80, 64), this->game->audio_manager.get_music_volume(), 48, 1);
    fs_slider = FullscreenSlider(game, Vector2(80,96), sdlgame::display::is_fullscreen() , 5, 1);
    back_button = BackButton(game);
    back_button.rect.setBottomRight(RESOLUTION_WIDTH - 2, RESOLUTION_HEIGHT - 2);
}
Option::Option() = default;
void Option::update()
{
    sfx_slider.update();
    music_slider.update();
    back_button.update();
    fs_slider.update();
}
void Option::handle_event(Event &event)
{
    sfx_slider.handle_event(event);
    music_slider.handle_event(event);
    back_button.handle_event(event);
    fs_slider.handle_event(event);
}
void Option::draw()
{
    sfx_slider.draw();
    music_slider.draw();
    fs_slider.draw();
    this->game->window.blit(this->back_button.image,this->back_button.rect.getTopLeft());
}