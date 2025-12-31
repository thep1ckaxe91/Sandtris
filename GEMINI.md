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
