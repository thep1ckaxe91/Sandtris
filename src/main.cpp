#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>
#include <iostream>

#include "Game.hpp" // Your existing architecture, but cleaned up

// SYSTEMS CONSTANTS
// We want exactly 60 physics updates per second for stable sand simulation.
constexpr double MS_PER_UPDATE = 1000.0 / 60.0;

int main(int argc, char* argv[]) {
    // 1. Initialization (RAII style - if Game throws, we exit cleanly)
    try {
        Game sandtrisApp("Sandtris Reborn", 800, 600);

        // 2. The High-Precision Loop
        // We use std::chrono for nanosecond precision, avoiding integer truncation errors.
        using clock = std::chrono::high_resolution_clock;
        auto previous = clock::now();
        double lag = 0.0;

        bool isRunning = true;
        while (isRunning) {
            auto current = clock::now();
            std::chrono::duration<double, std::milli> elapsed = current - previous;
            previous = current;
            lag += elapsed.count();

            // 3. Input Processing (Happens every frame)
            // In SDL3, event polling is fast.
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
                sandtrisApp.handleEvent(event);
            }

            // 4. Fixed Update Step (The "Physics" Loop)
            // If the game lags, we run multiple updates to catch up.
            // This prevents the sand from "tunneling" through the floor.
            while (lag >= MS_PER_UPDATE) {
                sandtrisApp.update(); // Update SandGrid, Scene logic
                lag -= MS_PER_UPDATE;
            }

            // 5. Render (The "Visual" Loop)
            // Pass 'lag / MS_PER_UPDATE' if you want interpolation (smooth movement),
            // but for a pixel-sand game, 0.0 is usually fine.
            sandtrisApp.render();
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}