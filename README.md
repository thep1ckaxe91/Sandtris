# Sandtris

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![Build System](https://img.shields.io/badge/Build-CMake%20%7C%20Conan%202-orange.svg)](https://conan.io/)
[![Engine](https://img.shields.io/badge/Engine-libsdlgame-green.svg)](https://github.com/thep1ckaxe91/libsdlgame)

A falling sand puzzle game merging classic Tetris tetromino mechanics with falling-sand cellular automata physics, re-architected with **C++23** for high performance, strict RAII lifecycle management, and scalable simulation.

---

## Overview

Sandtris simulates sand particles on a discrete grid where falling tetromino blocks dissolve into falling sand granules upon settling. Connected granules of the same color spanning from the left barrier to the right barrier trigger flood-fill line clears and score points.

This repository represents an extensive performance refactor of the original game logic, transitioning from monolithic Pygame-style scripts into a modular, production-grade systems architecture:
- **Language Standard**: Modern ISO C++23.
- **Engine Decoupling**: Game engine utilities decoupled into an independent library ([`libsdlgame`](https://github.com/)), consuming SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer.
- **Memory Model**: Strict RAII compliance with zero raw pointer ownership on the critical path.
- **Package Management**: Conan 2.x for reproducible, multi-configuration dependency resolution.
- **Diagnostics & Testing**: Integrated AddressSanitizer/UBSan runtime instrumentation, GoogleTest test runner, and Linux `perf`/`hotspot` profiling integration.

---

## Architectural Highlights

```
Sandtris/
├── assets/                  # Runtime textures, audio stems, and TTF fonts
├── include/                 # Game domain headers
│   ├── Grid.hpp             # Cellular automata grid & sand simulation
│   ├── TetriminoController.hpp # Falling piece input & collision response
│   ├── Scene.hpp            # State machine interface for game scenes
│   └── constant.hpp         # Core simulation constants & bitmask definitions
├── src/                     # Game implementation files
│   ├── main.cpp             # Engine bootstrap, game loop & benchmark stats
│   ├── Grid.cpp             # Sand step physics & scoring BFS
│   └── ...
├── tests/                   # GoogleTest unit & regression suite
├── profiling results/       # Optimization case studies & flame graphs
├── CMakeLists.txt           # Target definitions & warning flags
├── conanfile.py             # Conan 2.x dependency specification
└── makefile                 # Front-end build & profiling orchestrator
```

### Core Systems
- **Cellular Automata Grid (`Grid`)**: Sand particles operate over an $80 \times 176$ grid (`GRID_WIDTH` $\times$ `GRID_HEIGHT`), stepping through diagonal settling rules and updating streaming textures via direct pixel buffer access.
- **Bitmask Tetrominoes (`Tetrimino`)**: Shapes and rotations are encoded into 16-bit integer masks (`uint16_t`) for instantaneous bitwise collision detection against bounds and barriers.
- **Scoring Pipeline (`check_scoring`)**: Breadth-First Search (BFS) combined with 2D `std::bitset` arrays traverses connected sand groups to identify and clear contiguous color bridges between boundaries.
- **Scene State Machine (`Scene`, `SceneTransition`)**: Polymorphic stack transitions managing menu flows, pause states, and game loop lifecycles.

---

## Prerequisites

- **OS**: Linux (developed and verified on EndeavourOS / Arch-based Linux, GCC 14+ / Clang 16+)
- **Build Tools**:
  - `cmake` (>= 3.24)
  - `conan` (>= 2.0)
  - GNU `make`
  - `g++` or `clang++` with C++23 support
- **Optional Profiling Tools**:
  - `linux-tools` / `perf`
  - `hotspot` (GUI performance flame graph viewer)

---

## Building and Running

The project utilizes a top-level GNU `makefile` as an ergonomic frontend over Conan 2.x presets and CMake.

### 1. Fast Build (RelWithDebInfo - Default)
Generates optimized code with debug symbols and runtime sanitizers enabled:
```bash
make
# or explicitly:
make relwithdebinfo_build
```

### 2. Debug Build
Enables `-g3 -O0` and AddressSanitizer/UBSan for debugging:
```bash
make debug_build
```

### 3. Release Build
Stripped, fully optimized binary (`-O3 -DNDEBUG`):
```bash
make release_build
```

### 4. Running the Executable
After building, binaries are located in the configuration-specific build directory:
```bash
# Run the RelWithDebInfo build:
./build/RelWithDebInfo/Sandtris

# Run the Debug build:
./build/Debug/Sandtris
```

### 5. Running Automated Tests
GoogleTest targets are built automatically alongside the main target:
```bash
ctest --test-dir build/RelWithDebInfo --output-on-failure
```

---

## Profiling and Benchmarking

High-performance optimization is a core pillar of this repository. Built-in hooks are provided for profiling the simulation:

### Hotspot & Linux Perf
To sample call stacks and inspect flame graphs using `perf` and `hotspot`:
```bash
make hotspot
```
This runs a 99Hz DWARF call-graph recording session on the `RelWithDebInfo` binary and opens the resulting `perf.data` inside Hotspot.

### Documented Optimization Passes
Detailed post-mortems and flame graph analyses from previous optimization cycles are archived in the repository:
- [**Redundancy Optimization**](./profiling%20results/Redundancy/Redundancy%20Optimization.md): Elimination of redundant texture locks and unneeded ghost updates, achieving a **~30x speedup** in the core frame loop.
- [**Architecture Optimization**](./profiling%20results/Architecture/Architecture%20Optimization.md): High-resolution timer refactoring using `std::chrono` and cache-friendly ring buffers.

---

## Housekeeping & Cleaning

- Clean object files for active configurations:
  ```bash
  make clean
  ```
- Purge all generated build trees and CMake presets:
  ```bash
  make distclean
  ```

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
