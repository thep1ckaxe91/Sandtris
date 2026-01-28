# Sandtris Project

## Project Overview

This project, Sandtris, is a 2D falling sand simulation game written in C++. It leverages the SDL2 library for graphics, audio, and input. The primary focus of this project is on performance and scalability, with the goal of simulating a large number of sand particles efficiently.

The project is structured into two main components:

*   **`engine/`**: A custom game engine providing core functionalities like display management, drawing, event handling, and resource management.
*   **`src/`**: The main application logic, including the game loop, scene management, and game-specific features.

The project is built using CMake and is configured to use C++23.

## Building and Running

To build and run the project, execute the following command from the root directory:

```bash
./run_build.sh
```

This script will handle the CMake configuration, build the project, and run the executable.

## Development Conventions

*   **C++23**: The project uses modern C++ features and standards.
*   **SDL2**: The project relies on the SDL2 library and its extensions (SDL2_image, SDL2_mixer, SDL2_ttf).
*   **CMake**: The build system is managed through CMake.
*   **Performance Profiling**: The code includes a custom timer and statistics printing, indicating a focus on performance analysis and optimization.
*   **Scene-based Architecture**: The game is structured around scenes, which encapsulate different parts of the game (e.g., main menu, gameplay, game over).
*   **Header-only Libraries**: The `engine/include` directory contains header files that are publicly accessible to any library that links against the `GameEngine`.
