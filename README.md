# Sandtris: A Performance-Focused Refactor

This repository is a refactor of the original Sandtris project, with a primary focus on **performance and scalability**. The goal is to evolve the engine to handle a significantly larger number of sand particles, pushing the boundaries of what's possible for a 2D falling sand simulation in C++.

## Project Goals

1.  **Massive-Scale Simulation:** The primary objective is to optimize the core sand simulation algorithm to support a much higher resolution grid and a vastly larger number of concurrent sand particles.
2.  **Modern C++ Idioms:** The original project, while functional, used some outdated C++ practices. This refactor will modernize the codebase by:
    *   Adopting RAII and smart pointers (`std::unique_ptr`, `std::shared_ptr`) to eliminate manual memory management.
    *   Replacing non-standard headers like `<bits/stdc++.h>` with specific includes.
    *   Removing `using namespace std;` from header files.
    *   Improving portability by using `std::filesystem` for path management.
3.  **Multithreading:** The existing multithreading implementation will be re-evaluated and potentially replaced with a more efficient, modern approach to parallelizing the grid update logic.

4. **Architechture:** Seperate core logic from app logic. (It already is, but kinda wrong to say it's not binded)

## Current Status

The project is currently in the process of being refactored. The original `GEMINI.md` file provides a detailed analysis of the initial state of the codebase. This `README.md` and the new `GEMINI.md` will guide the development process.

## Building and Running

Run:
```bash
./run_build.sh
```

