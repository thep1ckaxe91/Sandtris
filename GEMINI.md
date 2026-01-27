# Gemini Code Assistant Context

This document provides context for the Gemini code assistant to understand the Sandtris project.

## Project Overview

Sandtris is a 2D falling sand simulation game written in C++. It appears to be a Tetris-like game with sand physics. The project is a refactor of an older version, with a focus on performance, scalability, and modern C++ practices.

The game uses the following technologies:
- **Language:** C++20
- **Build System:** CMake
- **Libraries:**
    - SDL2
    - SDL2_image
    - SDL2_mixer
    - SDL2_ttf

The project is structured into a core engine and the main game logic. The engine provides functionalities for display, drawing, audio, and input, while the game logic implements the game's scenes and gameplay mechanics.

## Building and Running

The project can be built and run using the provided `run_build.sh` script. This script performs the following steps:
1.  Configures the project with CMake, creating a `build` directory.
2.  Compiles the project using the available number of processor cores.
3.  Runs the game executable `Sandtris`.

To build and run the game, execute the following command in the project's root directory:
```bash
./run_build.sh
```

## Project Structure

The project is organized into the following main directories:
- `assets/`: Contains game assets such as images, animations, fonts, and audio.
- `engine/`: The core game engine, providing a hardware abstraction layer and common functionalities.
    - `include/`: Header files for the engine.
    - `src/`: Source files for the engine.
- `include/`: Header files for the game logic.
- `src/`: Source files for the game logic, including the main entry point (`main.cpp`) and various game scenes.
- `build/`: The build directory, where the compiled executable and assets are placed.

## Development Conventions

- The project uses C++20 and modern C++ idioms, including RAII and smart pointers.
- Header files are located in the `include` and `engine/include` directories.
- Source files are located in the `src` and `engine/src` directories.
- The codebase is organized into scenes, with each scene representing a different part of the game (e.g., main menu, gameplay, game over).
- The `Game` class in `src/main.cpp` manages the main game loop and scene transitions.
- The project uses a custom engine that wraps SDL functionalities.
- All game assets are stored in the `assets` directory and copied to the build directory after compilation.
