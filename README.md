# Sandtris: A Performance-Focused Refactor

This repository is a refactor of the original Sandtris project, with a primary focus on **performance and scalability**. The goal is to evolve the engine to handle a significantly larger number of sand particles, pushing the boundaries of what's possible for a 2D falling sand simulation in C++.

## Performance Optimization

The main focus of this refactor is to optimize the game's performance. The process and results of these optimizations are documented in the following files:

*   [**Redundancy Optimization**](./profiling%20results/Redundancy/Redundancy%20Optimization.md): This document details the process of identifying and removing redundant work in the game's main loop, resulting in a **~30 times faster** main loop.
*   [**Architecture Optimization**](./profiling%20results/Architecture/Architecture%20Optimization.md): This document covers the architectural changes made to the project to improve performance, such as refactoring the `time` namespace to use `std::chrono` and a ring buffer.

## Building and Running

To build and run the project, execute the following command from the root directory:

```bash
./run_build.sh
```