# Sandtris: Performance-Focused Falling Sand Simulation

Sandtris is a 2D falling sand simulation game built with C++23. It's a refactor of an earlier project, specifically optimized for high performance and scalability to handle a massive number of sand particles.

## Project Overview

- **Core Technologies:** C++23, SDL2, CMake, Conan.
- **Engine Architecture:** A custom-built `GameEngine` (located in `engine/`) provides a hardware abstraction layer for graphics, audio, input, and time management.
- **Game Logic:** Implemented using a scene-based architecture where the `Game` class manages scene transitions and the main loop.
- **Performance:** Extensive profiling and optimization work has been done, including redundant work removal and architectural refactoring (e.g., `time` namespace with `std::chrono` and ring buffers).

## Building and Running

The project uses **Conan** for dependency management and **CMake** for building.

### Prerequisites
- C++23 compatible compiler (e.g., GCC 13+, Clang 16+)
- CMake 3.24+
- Conan 2.x

### Build Steps (Inferred)
1.  **Install Dependencies:**
    ```bash
    conan install . --output-folder=build --build=missing
    ```
2.  **Configure CMake:**
    ```bash
    cmake --preset conan-release
    ```
3.  **Build the Project:**
    ```bash
    cmake --build --preset conan-release
    ```
4.  **Run the Game:**
    The executable `Sandtris` will be located in the build output directory (e.g., `build/Release/Sandtris`).

*Note: Assets in the `assets/` directory are automatically copied to the build directory as a post-build step.*

## Development Conventions

### Architectural Patterns
- **Scene Management:** The game operates through discrete scenes (e.g., `MainMenu`, `GamePlay`, `GameOver`). Use `Game::add_scene`, `Game::pop_scene`, and `Game::clear_scene` for transitions.
- **Memory Management:** While the engine uses RAII, some game-level pointers (like `SceneTransition`) require manual cleanup or careful management as noted in `Game.hpp`.
- **Performance-First Design:** All major changes should be evaluated for performance impact. Check `profiling results/` for historical context and methodologies. The `Sand` struct is optimized to be extremely small (e.g., 2 bytes) to minimize memory overhead.

### Coding Style
- **C++ Standards:** Adhere to C++23 standards and modern idioms.
- **Engine Wrappers:** Use the `sdlgame` namespace provided by the engine for SDL-related operations instead of calling SDL directly when possible.
- **Profiling:** Utilize the `Timer` and `TimerManager` classes from the `sdlgame::time` namespace for benchmarking critical paths.

### Asset Handling
- Images, animations, audio, and fonts should be placed in their respective subdirectories within `assets/`.
- New assets added to `assets/` will be copied to the build directory upon the next successful build.
