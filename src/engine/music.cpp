// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "music.hpp"
#include "mixer.hpp" // for _mixer_device
#include <string>
#include <memory>
#include "SDL3/SDL.h"

namespace sdlgame::music {

std::shared_ptr<MIX_Audio> music_audio;
MIX_Track *music_track = nullptr;

void load(std::string path) {
    if (music_track) {
        MIX_DestroyTrack(music_track);
        music_track = nullptr;
    }
    music_audio.reset(MIX_LoadAudio(path.c_str()), MIX_FreeAudio);
    if (!music_audio) {
        SDL_Log("Can't load music: %s", SDL_GetError());
        exit(1);
    }
}

void play(int loop, int fadein_ms) {
    if (!music_audio) {
        return;
    }

    if (music_track) {
        MIX_DestroyTrack(music_track);
    }

    music_track = MIX_CreateTrack(sdlgame::mixer::_mixer_device, music_audio.get());
    if(!music_track) {
        SDL_Log("Failed to create music track: %s", SDL_GetError());
        return;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_TRACK_PLAY_LOOP_COUNT, loop);
    if (fadein_ms > 0) {
        SDL_SetNumberProperty(props, MIX_PROP_TRACK_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadein_ms);
    }

    if(!MIX_PlayTrack(music_track, props)) {
        SDL_Log("Can't play music: %s", SDL_GetError());
        MIX_DestroyTrack(music_track);
        music_track = nullptr;
    }
    SDL_DestroyProperties(props);
}

void pause() {
    if (music_track) {
        MIX_PauseTrack(music_track);
    }
}

void resume() {
    if (music_track) {
        MIX_ResumeTrack(music_track);
    }
}

void stop() {
    if (music_track) {
        MIX_DestroyTrack(music_track);
        music_track = nullptr;
    }
}

bool is_playing() {
    if (music_track) {
        return MIX_IsTrackPlaying(music_track);
    }
    return false;
}

double duration() {
    if (music_audio) {
        return MIX_GetAudioDuration(music_audio);
    }
    return 0.0;
}

void set_volume(float value) {
    if (music_track) {
        MIX_SetTrackGain(music_track, value);
    }
}

float get_volume() {
    if (music_track) {
        return MIX_GetTrackGain(music_track);
    }
    return 0.0f;
}

} // namespace sdlgame::music
