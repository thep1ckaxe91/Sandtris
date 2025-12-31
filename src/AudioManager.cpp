#include "AudioManager.hpp"
#include "TetrisEvent.hpp"
#include "SaveData.hpp"
AudioManager::AudioManager()
{
    sfx.load();
    sfx_volume = ::get_sfx_volume();
    music_volume = ::get_music_volume();
    this->set_sfx_volume(sfx_volume);
    this->set_music_volume(music_volume);
}
void AudioManager::handle_event(Event &event)
{
    switch (event.type)
    {
    case BUTTON_CLICK:
        sfx.button_click.play();
        break;
    case BUTTON_HOVER:
        sfx.button_hover.play();
        break;
    case COUNT_DOWN:
        sfx.count_down.play();
        break;
    case COUNT_DOWN_START:
        sfx.count_down_start.play();
        break;
    case GAMEOVER:
        sfx.game_over.play();
        break;
    case MERGING:
        sfx.merge.play();
        break;
    case ROTATE:
        sfx.rotate.play();
        break;
    case SCORING:
        sfx.scoring.play();
        break;
    case SCENETRANS_IN:
        sfx.transition_in.play();
        break;
    case SCENETRANS_OUT:
        sfx.transition_out.play();
        break;
    default:
        break;
    }
}
void AudioManager::update()
{
}
void AudioManager::set_sfx_volume(float value)
{
    this->sfx_volume = value;
    sfx.button_click.set_volume(value);
    sfx.button_hover.set_volume(value);
    sfx.count_down.set_volume(value);
    sfx.count_down_start.set_volume(value);
    sfx.game_over.set_volume(value);
    sfx.merge.set_volume(value);
    sfx.rotate.set_volume(value);
    sfx.scoring.set_volume(value);
    sfx.transition_in.set_volume(value);
    sfx.transition_out.set_volume(value);
    sfx.soft_wind_blow.set_volume(value);
    ::set_sfx_volume(value);
}
void AudioManager::set_music_volume(float value)
{
    this->music_volume = value;
    sdlgame::music::set_volume(value);
    ::set_music_volume(value);
}
float AudioManager::get_sfx_volume()
{
    sfx_volume = ::get_sfx_volume();
    return sfx_volume;
}
float AudioManager::get_music_volume()
{
    music_volume = ::get_music_volume();
    return music_volume;
}