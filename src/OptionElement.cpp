#include "OptionElement.hpp"
#include "SaveData.hpp"
SFXVolumeSlider::SFXVolumeSlider(Game &game, Vector2 topleft, float val, float length, float max_val) : Slider(topleft, val, length, max_val)
{

    this->game = &game;
    this->set_color("white", "white", "gray");
    this->set_label("SFX Volume: ", "white");
}
SFXVolumeSlider::SFXVolumeSlider() = default;
void SFXVolumeSlider::update()
{
    Slider::update();
}
void SFXVolumeSlider::handle_event(Event &event)
{
    Slider::handle_event(event);
}
void SFXVolumeSlider::draw()
{
    this->game->window.blit(this->label_surf, label_rect.getTopLeft());
    sdlgame::draw::line(this->game->window, this->value_color, topleft, topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::line(this->game->window, this->no_value_color, topleft + Vector2(slide_length, 0), topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::rect(this->game->window, this->nob_color, nob);
}
void SFXVolumeSlider::on_change_value()
{
    this->game->audio_manager.set_sfx_volume(this->value / this->max_value);
}

MusicVolumeSlider::MusicVolumeSlider(Game &game, Vector2 topleft, float val, float length, float max_val) : Slider(topleft, val, length, max_val)
{

    this->game = &game;
    this->set_color("white", "white", "gray");
    this->set_label("Music Volume: ", "white");
}
MusicVolumeSlider::MusicVolumeSlider() = default;
void MusicVolumeSlider::update()
{
    Slider::update();
}
void MusicVolumeSlider::handle_event(Event &event)
{
    Slider::handle_event(event);
}
void MusicVolumeSlider::draw()
{
    this->game->window.blit(this->label_surf, label_rect.getTopLeft());
    sdlgame::draw::line(this->game->window, this->value_color, topleft, topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::line(this->game->window, this->no_value_color, topleft + Vector2(slide_length, 0), topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::rect(this->game->window, this->nob_color, nob);
}
void MusicVolumeSlider::on_change_value()
{
    this->game->audio_manager.set_music_volume(this->value / this->max_value);
}

FullscreenSlider::FullscreenSlider(Game &game, Vector2 topleft, float value, float length, float max_value) : Slider(topleft, value, length, max_value)
{
    this->game = &game;
    this->set_color("white", "orange", "saddle brown");
    this->set_label("Fullscreen :", "white");
}
FullscreenSlider::FullscreenSlider() = default;
void FullscreenSlider::update()
{
    this->nob.setCenter(this->topleft + Vector2(this->value * this->slide_length / this->max_value, 0));
}
void FullscreenSlider::handle_event(Event &event)
{
    Slider::handle_event(event);
}
void FullscreenSlider::draw()
{
    this->game->window.blit(this->label_surf, label_rect.getTopLeft());
    sdlgame::draw::line(this->game->window, this->value_color, topleft, topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::line(this->game->window, this->no_value_color, topleft + Vector2(slide_length, 0), topleft + Vector2(this->slide_length, 0) * (this->value / this->max_value));
    sdlgame::draw::rect(this->game->window, this->nob_color, nob);
}
void FullscreenSlider::on_change_value()
{
    this->value = (this->value == 0 ? this->max_value : 0);
    if (this->value != this->max_value)
    {
        pair<int, int> reso = load_window_info().second;
        if (reso.first == 0)
        {
            sdlgame::display::maximize();
        }
        else
        {
            sdlgame::display::set_window_size(reso.first, reso.second);
        } // cout << "call restore" << endl;
    }
    else
    {
        sdlgame::display::fullscreen_desktop();
        // cout << "call fullscreen" << endl;
    }
}