# Sandtris: Refactor for Performance - Technical Guide

## 1. Project Objective

The primary goal of this project is to refactor the Sandtris game to significantly improve its performance and scalability, allowing it to simulate a much larger number of sand particles at a higher resolution. A secondary goal is to modernize the C++ codebase to align with current best practices.

## 2. Game Engine

The game is built upon a custom C++ engine that acts as a thin wrapper around the SDL3 library. Its design is heavily inspired by the Pygame library, providing a familiar API for developers coming from a Python background.

### 2.1. Engine Architecture

The engine is composed of several modules, each responsible for a specific aspect of the game's functionality:

*   **Core (`engine.hpp`, `engine.cpp`):** Handles initialization and shutdown of the engine.
*   **Display (`display.hpp`, `display.cpp`):** Manages the game window and rendering surface.
*   **Drawing (`draw.hpp`, `draw.cpp`):** Provides functions for drawing primitive shapes and surfaces.
*   **Event (`event.hpp`, `event.cpp`):** Handles user input and window events.
*   **Font (`font.hpp`, `font.cpp`):** Manages font loading and text rendering.
*   **Image (`image.hpp`, `image.cpp`):** Handles image loading.
*   **Audio (`mixer.hpp`, `mixer.cpp`, `music.hpp`, `music.cpp`):** Manages sound effects and music.
*   **Time (`time.hpp`, `time.cpp`):** Provides functionality for controlling the game's frame rate.
*   **And more:** Includes modules for math, rectangles, surfaces, sprites, transformations, keyboard/mouse input, and colors.

### 2.2. Current Limitations

*   **Single-threaded:** The engine is not thread-safe and should only be used in a single-threaded context.
*   **Platform Support:** Currently, the engine is only confirmed to work on Windows.
*   **Build System:** The project uses CMake, but the current `CMakeLists.txt` is incomplete and needs to be updated to include all the engine and game source files.

## 3. Core Refactoring Areas

Based on the initial analysis, the following areas are the main focus for refactoring:

### 3.1. Memory Management (High Priority)

*   **Objective:** Eliminate manual memory management to prevent memory leaks and improve code safety.
*   **Action Items:**
    *   Replace raw `new` and `delete` with `std::unique_ptr` for all `Scene` and `SceneTransition` objects within the `Game` class. The `Game` class is the single owner of these objects.
    *   Audit the rest of the codebase for any other raw pointer usage and replace it with appropriate smart pointers.

### 3.2. Sand Simulation Algorithm (High Priority)

*   **Objective:** Optimize the sand simulation logic in the `Grid` class to handle a massive number of particles.
*   **Action Items:**
    *   Analyze the current `step()` function in the `Grid` class for performance bottlenecks.
    *   Investigate more efficient algorithms for updating the sand particles, such as chunking the grid and only updating active chunks.
    *   Profile the application to identify the most time-consuming parts of the simulation.

### 3.3. Multithreading (Medium Priority)

*   **Objective:** Implement an efficient multithreading strategy for the grid update.
*   **Action Items:**
    *   Remove the existing `#ifdef MULTITHREADING` implementation.
    *   Design and implement a more robust and efficient multithreading model. A thread pool that processes chunks of the grid could be a good approach.
    *   Ensure that the multithreading implementation is thread-safe and does not introduce race conditions.

### 3.4. Code Modernization (Medium Priority)

*   **Objective:** Bring the codebase up to modern C++ standards.
*   **Action Items:**
    *   Replace all instances of `#include <bits/stdc++.h>` with specific headers, both in the game and engine code.
    *   Remove all `using namespace std;` from header files. Qualify names with `std::` or use `using` declarations in `.cpp` files.
    *   Replace all Windows-specific path constructions (e.g., `"data\fonts\"`) with `std::filesystem::path` to ensure cross-platform compatibility.
    *   Standardize I/O operations to use C++ streams (`std::cout`, `std::cerr`) instead of C-style functions (`printf`).

## 4. Build and Run Instructions

The project is built using CMake.

1.  **Configure:** `cmake -B build`
2.  **Build:** `cmake --build build`
3.  **Run:** `./build/Debug/Sandtris` (or similar, depending on the build type and target name)

This document should be used as a guide for all future development on this project.

---
## 5. Architecture Mandates (as of 2025-12-10)

These mandates are from a `SYSTEM_CONTEXT_UPDATE` and take precedence over the general guidelines above where conflicts exist.

*   **Role**: Senior Systems Engineer / C++ Performance Specialist.
*   **Project**: Sandtris (Refactoring Legacy C++ to Modern Systems C++20).

### 5.1. Build System
*   CMake with explicit source lists. No GLOBs.

### 5.2. Library
*   SDL3 (Not SDL2).

### 5.3. Memory Management
*   RAII enforcement. No raw 'new/delete'.
*   Use `std::unique_ptr` with custom deleters for SDL resources.

### 5.4. Performance Strategy
*   **Rendering**: DO NOT use `SDL_RenderPoint`. Use `SDL_LockTexture` + direct buffer manipulation (`uint32_t` array).
*   **Physics**: Iterate 1D memory linearly (cache-friendly) rather than naive 2D array access.
*   **Input**: Zero-allocation. Manipulate `Tetromino` structs (stack memory), do not create Surfaces for rotating pieces.

## 6. Current problem description
* **Migrations**: Due to the incompatibilities when migrate from SDL2 to SDL3, most of the tools in mixer.cpp and music.cpp is broken (and the structure in its header files too). All sort of problem even include memory leaks due to Track not getting destroy

## 7. TODO

1. restructure the header files, rewrite the source file while maintain the behaviour of the functions.
2. use modern C++ practice like smart pointer to manage memory, allow more safe memory management
3. be aware of the variables life cycle and move ownership when needed
4. For now only do this for music.cpp, mixer.cpp and its header files

## 8. SDL3 Mixer APIs

```cpp
// SDL3_mixer API Quick Reference
//
// https://libsdl.org/projects/SDL_mixer/
//
// The latest version of this document can be found at https://wiki.libsdl.org/SDL3_mixer/QuickReference
// Based on SDL_mixer version 3.1.0
//
// This can be useful in an IDE with search and syntax highlighting.
//
// Original idea for this document came from Dan Bechard (thanks!)
// ASCII art generated by: https://patorjk.com/software/taag/#p=display&f=ANSI%20Shadow (with modified 'S' for readability)

#define SDL_MIXER_MAJOR_VERSION                                                                                                          // The current major version of SDL_mixer headers.
#define SDL_MIXER_MINOR_VERSION                                                                                                          // The current minor version of the SDL_mixer headers.
#define SDL_MIXER_MICRO_VERSION                                                                                                          // The current micro (or patchlevel) version of the SDL_mixer headers.
#define SDL_MIXER_VERSION                                                                                                                // This is the current version number macro of the SDL_mixer headers.
#define SDL_MIXER_VERSION_ATLEAST(X, Y, Z)                                                                                               // This macro will evaluate to true if compiled with SDL_mixer at least X.Y.Z.
int MIX_Version(void);                                                                                                                   // Get the version of SDL_mixer that is linked against your program.
bool MIX_Init(void);                                                                                                                     // Initialize the SDL_mixer library.
void MIX_Quit(void);                                                                                                                     // Deinitialize the SDL_mixer library.
int MIX_GetNumAudioDecoders(void);                                                                                                       // Report the number of audio decoders available for use.
const char * MIX_GetAudioDecoder(int index);                                                                                             // Report the name of a specific audio decoders.
MIX_Mixer * MIX_CreateMixerDevice(SDL_AudioDeviceID devid, const SDL_AudioSpec *spec);                                                   // Create a mixer that plays sound directly to an audio device.
MIX_Mixer * MIX_CreateMixer(const SDL_AudioSpec *spec);                                                                                  // Create a mixer that generates audio to a memory buffer.
void MIX_DestroyMixer(MIX_Mixer *mixer);                                                                                                 // Free a mixer.
SDL_PropertiesID MIX_GetMixerProperties(MIX_Mixer *mixer);                                                                               // Get the properties associated with a mixer.
bool MIX_GetMixerFormat(MIX_Mixer *mixer, SDL_AudioSpec *spec);                                                                          // Get the audio format a mixer is generating.
MIX_Audio * MIX_LoadAudio_IO(MIX_Mixer *mixer, SDL_IOStream *io, bool predecode, bool closeio);                                          // Load audio for playback from an SDL_IOStream.
MIX_Audio * MIX_LoadAudio(MIX_Mixer *mixer, const char *path, bool predecode);                                                           // Load audio for playback from a file.
MIX_Audio * MIX_LoadAudioWithProperties(SDL_PropertiesID props);                                                                         // Load audio for playback through a collection of properties.
MIX_Audio * MIX_LoadRawAudio_IO(MIX_Mixer *mixer, SDL_IOStream *io, const SDL_AudioSpec *spec, bool closeio);                            // Load raw PCM data from an SDL_IOStream.
MIX_Audio * MIX_LoadRawAudio(MIX_Mixer *mixer, const void *data, size_t datalen, const SDL_AudioSpec *spec);                             // Load raw PCM data from a memory buffer.
MIX_Audio * MIX_LoadRawAudioNoCopy(MIX_Mixer *mixer, const void *data, size_t datalen, const SDL_AudioSpec *spec, bool free_when_done);  // Load raw PCM data from a memory buffer without making a copy.
MIX_Audio * MIX_CreateSineWaveAudio(MIX_Mixer *mixer, int hz, float amplitude);                                                          // Create a MIX_Audio that generates a sinewave.
SDL_PropertiesID MIX_GetAudioProperties(MIX_Audio *audio);                                                                               // Get the properties associated with a MIX_Audio.
Sint64 MIX_GetAudioDuration(MIX_Audio *audio);                                                                                           // Get the length of a MIX_Audio's playback in sample frames.
bool MIX_GetAudioFormat(MIX_Audio *audio, SDL_AudioSpec *spec);                                                                          // Query the initial audio format of a MIX_Audio.
void MIX_DestroyAudio(MIX_Audio *audio);                                                                                                 // Destroy the specified audio.
MIX_Track * MIX_CreateTrack(MIX_Mixer *mixer);                                                                                           // Create a new track on a mixer.
void MIX_DestroyTrack(MIX_Track *track);                                                                                                 // Destroy the specified track.
SDL_PropertiesID MIX_GetTrackProperties(MIX_Track *track);                                                                               // Get the properties associated with a track.
MIX_Mixer * MIX_GetTrackMixer(MIX_Track *track);                                                                                         // Get the MIX_Mixer that owns a MIX_Track.
bool MIX_SetTrackAudio(MIX_Track *track, MIX_Audio *audio);                                                                              // Set a MIX_Track's input to a MIX_Audio.
bool MIX_SetTrackAudioStream(MIX_Track *track, SDL_AudioStream *stream);                                                                 // Set a MIX_Track's input to an SDL_AudioStream.
bool MIX_SetTrackIOStream(MIX_Track *track, SDL_IOStream *io, bool closeio);                                                             // Set a MIX_Track's input to an SDL_IOStream.
bool MIX_SetTrackRawIOStream(MIX_Track *track, SDL_IOStream *io, const SDL_AudioSpec *spec, bool closeio);                               // Set a MIX_Track's input to an SDL_IOStream providing raw PCM data.
bool MIX_TagTrack(MIX_Track *track, const char *tag);                                                                                    // Assign an arbitrary tag to a track.
void MIX_UntagTrack(MIX_Track *track, const char *tag);                                                                                  // Remove an arbitrary tag from a track.
bool MIX_SetTrackPlaybackPosition(MIX_Track *track, Sint64 frames);                                                                      // Seek a playing track to a new position in its input.
Sint64 MIX_GetTrackPlaybackPosition(MIX_Track *track);                                                                                   // Get the current input position of a playing track.
bool MIX_TrackLooping(MIX_Track *track);                                                                                                 // Query whether a given track is looping.
MIX_Audio * MIX_GetTrackAudio(MIX_Track *track);                                                                                         // Query the MIX_Audio assigned to a track.
SDL_AudioStream * MIX_GetTrackAudioStream(MIX_Track *track);                                                                             // Query the SDL_AudioStream assigned to a track.
Sint64 MIX_GetTrackRemaining(MIX_Track *track);                                                                                          // Return the number of sample frames remaining to be mixed in a track.
Sint64 MIX_TrackMSToFrames(MIX_Track *track, Sint64 ms);                                                                                 // Convert milliseconds to sample frames for a track's current format.
Sint64 MIX_TrackFramesToMS(MIX_Track *track, Sint64 frames);                                                                             // Convert sample frames for a track's current format to milliseconds.
Sint64 MIX_AudioMSToFrames(MIX_Audio *audio, Sint64 ms);                                                                                 // Convert milliseconds to sample frames for a MIX_Audio's format.
Sint64 MIX_AudioFramesToMS(MIX_Audio *audio, Sint64 frames);                                                                             // Convert sample frames for a MIX_Audio's format to milliseconds.
Sint64 MIX_MSToFrames(int sample_rate, Sint64 ms);                                                                                       // Convert milliseconds to sample frames at a specific sample rate.
Sint64 MIX_FramesToMS(int sample_rate, Sint64 frames);                                                                                   // Convert sample frames, at a specific sample rate, to milliseconds.
bool MIX_PlayTrack(MIX_Track *track, SDL_PropertiesID options);                                                                          // Start (or restart) mixing a track for playback.
bool MIX_PlayTag(MIX_Mixer *mixer, const char *tag, SDL_PropertiesID options);                                                           // Start (or restart) mixing all tracks with a specific tag for playback.
bool MIX_PlayAudio(MIX_Mixer *mixer, MIX_Audio *audio);                                                                                  // Play a MIX_Audio from start to finish without any management.
bool MIX_StopTrack(MIX_Track *track, Sint64 fade_out_frames);                                                                            // Halt a currently-playing track, possibly fading out over time.
bool MIX_StopAllTracks(MIX_Mixer *mixer, Sint64 fade_out_ms);                                                                            // Halt all currently-playing tracks, possibly fading out over time.
bool MIX_StopTag(MIX_Mixer *mixer, const char *tag, Sint64 fade_out_ms);                                                                 // Halt all tracks with a specific tag, possibly fading out over time.
bool MIX_PauseTrack(MIX_Track *track);                                                                                                   // Pause a currently-playing track.
bool MIX_PauseAllTracks(MIX_Mixer *mixer);                                                                                               // Pause all currently-playing tracks.
bool MIX_PauseTag(MIX_Mixer *mixer, const char *tag);                                                                                    // Pause all tracks with a specific tag.
bool MIX_ResumeTrack(MIX_Track *track);                                                                                                  // Resume a currently-paused track.
bool MIX_ResumeAllTracks(MIX_Mixer *mixer);                                                                                              // Resume all currently-paused tracks.
bool MIX_ResumeTag(MIX_Mixer *mixer, const char *tag);                                                                                   // Resume all tracks with a specific tag.
bool MIX_TrackPlaying(MIX_Track *track);                                                                                                 // Query if a track is currently playing.
bool MIX_TrackPaused(MIX_Track *track);                                                                                                  // Query if a track is currently paused.
bool MIX_SetMasterGain(MIX_Mixer *mixer, float gain);                                                                                    // Set a mixer's master gain control.
float MIX_GetMasterGain(MIX_Mixer *mixer);                                                                                               // Get a mixer's master gain control.
bool MIX_SetTrackGain(MIX_Track *track, float gain);                                                                                     // Set a track's gain control.
float MIX_GetTrackGain(MIX_Track *track);                                                                                                // Get a track's gain control.
bool MIX_SetTagGain(MIX_Mixer *mixer, const char *tag, float gain);                                                                      // Set the gain control of all tracks with a specific tag.
bool MIX_SetTrackFrequencyRatio(MIX_Track *track, float ratio);                                                                          // Change the frequency ratio of a track.
float MIX_GetTrackFrequencyRatio(MIX_Track *track);                                                                                      // Query the frequency ratio of a track.
bool MIX_SetTrackOutputChannelMap(MIX_Track *track, const int *chmap, int count);                                                        // Set the current output channel map of a track.
bool MIX_SetTrackStereo(MIX_Track *track, const MIX_StereoGains *gains);                                                                 // Force a track to stereo output, with optionally left/right panning.
bool MIX_SetTrack3DPosition(MIX_Track *track, const MIX_Point3D *position);                                                              // Set a track's position in 3D space.
bool MIX_GetTrack3DPosition(MIX_Track *track, MIX_Point3D *position);                                                                    // Get a track's current position in 3D space.
MIX_Group * MIX_CreateGroup(MIX_Mixer *mixer);                                                                                           // Create a mixing group.
void MIX_DestroyGroup(MIX_Group *group);                                                                                                 // Destroy a mixing group.
SDL_PropertiesID MIX_GetGroupProperties(MIX_Group *group);                                                                               // Get the properties associated with a group.
MIX_Mixer * MIX_GetGroupMixer(MIX_Group *group);                                                                                         // Get the MIX_Mixer that owns a MIX_Group.
bool MIX_SetTrackGroup(MIX_Track *track, MIX_Group *group);                                                                              // Assign a track to a mixing group.
bool MIX_SetTrackStoppedCallback(MIX_Track *track, MIX_TrackStoppedCallback cb, void *userdata);                                         // Set a callback that fires when a MIX_Track is stopped.
bool MIX_SetTrackRawCallback(MIX_Track *track, MIX_TrackMixCallback cb, void *userdata);                                                 // Set a callback that fires when a MIX_Track has initial decoded audio.
bool MIX_SetTrackCookedCallback(MIX_Track *track, MIX_TrackMixCallback cb, void *userdata);                                              // Set a callback that fires when the mixer has transformed a track's audio.
bool MIX_SetGroupPostMixCallback(MIX_Group *group, MIX_GroupMixCallback cb, void *userdata);                                             // Set a callback that fires when a mixer group has completed mixing.
bool MIX_SetPostMixCallback(MIX_Mixer *mixer, MIX_PostMixCallback cb, void *userdata);                                                   // Set a callback that fires when all mixing has completed.
bool MIX_Generate(MIX_Mixer *mixer, void *buffer, int buflen);                                                                           // Generate mixer output when not driving an audio device.
MIX_AudioDecoder * MIX_CreateAudioDecoder(const char *path, SDL_PropertiesID props);                                                     // Create a MIX_AudioDecoder from a path on the filesystem.
MIX_AudioDecoder * MIX_CreateAudioDecoder_IO(SDL_IOStream *io, bool closeio, SDL_PropertiesID props);                                    // Create a MIX_AudioDecoder from an SDL_IOStream.
void MIX_DestroyAudioDecoder(MIX_AudioDecoder *audiodecoder);                                                                            // Destroy the specified audio decoder.
SDL_PropertiesID MIX_GetAudioDecoderProperties(MIX_AudioDecoder *audiodecoder);                                                          // Get the properties associated with a MIX_AudioDecoder.
bool MIX_GetAudioDecoderFormat(MIX_AudioDecoder *audiodecoder, SDL_AudioSpec *spec);                                                     // Query the initial audio format of a MIX_AudioDecoder.
int MIX_DecodeAudio(MIX_AudioDecoder *audiodecoder, void *buffer, int buflen, const SDL_AudioSpec *spec);  
```