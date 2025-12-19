// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mixer.hpp"
#include "SDL3/SDL.h"
#include <memory>
#include <vector>
#include <algorithm>

namespace sdlgame::mixer
{

    MIX_Mixer *_mixer_device = nullptr;
    std::vector<std::unique_ptr<MIX_Track, decltype(&MIX_DestroyTrack)>> _playing_tracks;

    void init(int freq, Uint16 size, int channels, int buffer)
    {
        if (!MIX_Init())
        {
            SDL_Log("Failed to initialize mixer: %s", SDL_GetError());
        }

        SDL_AudioSpec spec;
        spec.freq = freq;
        spec.format = SDL_AUDIO_F32;
        spec.channels = channels;

        if (!(_mixer_device = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec)))
        {
            SDL_Log("Failed to open audio device: %s", SDL_GetError());
            exit(1);
        }
    }

    void cleanup_finished_tracks()
    {
        if (_playing_tracks.empty())
        {
            return;
        }
        _playing_tracks.erase(
            std::remove_if(
                _playing_tracks.begin(),
                _playing_tracks.end(),
                [](const auto &track)
                {
                    return !MIX_TrackPlaying(track.get());
                }),
            _playing_tracks.end());
    }

    Sound::Sound() : volume(1.0f) {}

    Sound::Sound(std::string path) : volume(1.0f)
    {
        load(path);
    }

    void Sound::play(int loops, int maxtime_ms, int fade_ms)
    {
        if (!audio_ptr)
        {
            return;
        }

        MIX_Track *track = MIX_CreateTrack(_mixer_device);
        if (!track)
        {
            SDL_Log("Failed to create track: %s", SDL_GetError());
            return;
        }
        if (!MIX_SetTrackAudio(track, audio_ptr.get()))
        {
            SDL_Log("Can't set track audio: %s", SDL_GetError());
        }
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
        if (fade_ms > 0)
        {
            SDL_SetNumberProperty(props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fade_ms);
        }
        if (maxtime_ms > 0)
        {
            SDL_SetNumberProperty(props, MIX_PROP_PLAY_MAX_MILLISECONDS_NUMBER, maxtime_ms);
        }

        if (!MIX_PlayTrack(track, props))
        {
            SDL_Log("Can't play sound correctly: %s", SDL_GetError());
            MIX_DestroyTrack(track);
        }
        else
        {
            MIX_SetTrackGain(track, volume);
            _playing_tracks.emplace_back(track, MIX_DestroyTrack);
        }

        SDL_DestroyProperties(props);
    }

    void Sound::load(std::string path)
    {
        audio_ptr.reset(MIX_LoadAudio(_mixer_device, path.c_str(), true), MIX_DestroyAudio);
        if (!audio_ptr)
        {
            SDL_Log("Can't load audio: %s", SDL_GetError());
            exit(1);
        }
    }

    Sound& Sound::operator=(const Sound& other)
    {
        this->volume=other.get_volume();
        this->audio_ptr = other.audio_ptr;
    }

    void Sound::set_volume(float value)
    {
        volume = value;
    }

    float Sound::get_volume() const
    {
        return volume;
    }
    void quit()
    {
        MIX_Quit();
    }
}