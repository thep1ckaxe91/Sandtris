# Sandtris: A Performance-Focused Refactor

This repository is a refactor of the original Sandtris project, with a primary focus on **performance and scalability**. The goal is to evolve the engine to handle a significantly larger number of sand particles, pushing the boundaries of what's possible for a 2D falling sand simulation in C++.

## Project Goals

1.  **Massive-Scale Simulation:** The primary objective is to optimize the core sand simulation algorithm to support a much higher resolution grid and a vastly larger number of concurrent sand particles.
2.  **Modern C++ Idioms:** This refactor modernizes the codebase by adopting current C++ standards and best practices, such as smart pointers, proper header inclusion, and filesystem management.
3.  **Multithreading:** Re-evaluate and potentially replace the existing multithreading implementation with a more efficient, modern approach to parallelize the grid update logic.
4.  **Architecture:** Enforce a clearer separation between the core engine and game-specific logic.

## Project Structure

The project follows a classic game development architecture, separating the reusable game engine from the specific game logic.

*   **`engine/`**: This directory contains a custom-built 2D game engine that abstracts away the low-level details of the [SDL2](https://www.libsdl.org/) library. It provides modules for:
    *   `display`: Window and renderer management.
    *   `draw`: Primitives for drawing shapes and lines.
    *   `surface`: A wrapper around SDL_Texture for image manipulation.
    *   `event`: Event handling and propagation.
    *   `mixer`, `music`: Audio playback.
    *   And more for fonts, input, and math.

*   **`src/` and `include/`**: These directories contain the source code and headers for the Sandtris game itself. The logic is organized into a scene-based architecture, where each part of the game (main menu, gameplay, etc.) is a distinct `Scene`.

*   **`assets/`**: All external game assets, including graphics, fonts, and audio files, are located here.

## Key Components

The game's functionality is driven by a few key classes:

*   **`Game` (`src/main.cpp`)**: The main class that orchestrates the entire game. It manages the main game loop, scene transitions, and global game state.

*   **`Scene` (`include/Scene.hpp`)**: An abstract base class for all game scenes. Each scene (e.g., `MainMenu`, `GamePlay`, `Option`) implements its own `handle_event`, `update`, and `draw` methods. The `Game` class manages a stack of these scenes.

*   **`GamePlay` (`src/GamePlay.cpp`)**: The scene that contains the core gameplay. It manages the game grid, the player's score, and the overall state of a game session.

*   **`Grid` (`src/Grid.cpp`)**: This is where the main "sand" logic happens. It's a 2D grid that simulates the behavior of falling sand particles and manages the interaction between the Tetriminos and the sand.

*   **`TetriminoController` (`src/TetriminoController.cpp`)**: This class handles player input for moving and rotating the falling Tetrimino pieces.

*   **`Button` and `Slider` (`include/Button.hpp`, `include/Slider.hpp`)**: These are the base classes for the UI elements. Various specialized buttons (e.g., `StartButton`, `QuitButton`) inherit from the base `Button` class.

## Building and Running

To build and run the project, execute the following command from the root directory:
```bash
./run_build.sh
```
This script will:
1.  Configure the project using CMake into a `build` directory.
2.  Compile the source code.
3.  Run the final `Sandtris` executable.
