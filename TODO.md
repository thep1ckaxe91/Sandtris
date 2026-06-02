# Sandtris Refactor TODO List

This document tracks the tasks required for the performance and scalability refactor of Sandtris, based on the current `README.md` and project state.

The tasks are ordered in execution sequence, starting with memory and RAII cleanup, moving to data-oriented layout optimizations, and finally implementing concurrency and lock-free data structures.

## Phase 1: Memory Lifecycle Determinism & RAII
These tasks establish a predictable memory model and prevent leaks before we optimize allocations.

- [x] **Smart Pointer Migration:** Finalize wrapping the remaining legacy raw pointers (especially those from SDL2) in `std::unique_ptr` with custom SDL deleters to enforce strict RAII.
- [ ] **Arena Allocator Core:** Implement the custom `std::pmr` Arena Allocator to manage game state memory contiguously.
- [ ] **Operator Overloading:** Overload `operator new` and `operator delete` to completely bypass the OS heap scheduler on the critical path, utilizing the arena allocator.

## Phase 2: Data-Oriented Design & Cache-line Optimization
These tasks focus on CPU cache efficiency (L1/L2 hits) for single-threaded performance improvements.

- [ ] **Struct of Arrays (SoA):** Refactor entity and component memory layouts (such as sand particles and grid cells) to enforce contiguous linear scans, replacing Arrays of Structs (AoS).
- [ ] **False Sharing Mitigation:** Utilize `alignas(64)` to force atomic counters and frequently updated independent variables onto discrete CPU cache lines.

## Phase 3: Concurrency & Event Sourcing
These tasks parallelize the architecture and establish lock-free communication between threads.

- [ ] **SPSC Ring Buffer:** Implement a single-producer, single-consumer lock-free ring buffer utilizing `std::atomic<size_t>` for event sourcing and state updates.
- [ ] **Memory Ordering:** Enforce correct C++ atomic memory semantics: use `std::memory_order_release` when updating the write index and `std::memory_order_acquire` when reading from the ring buffer.
- [ ] **Game Loop Refactoring:** Architect the simulation as a deterministic fold over the lock-free ring buffer of immutable structs, decoupling the physics simulation from the rendering loop.

## Notes
- As per project rules, any refactoring action must be done in a separate branch and verified before merging.
- Ensure that the refactored features are self-tested.
- Preserve legacy comments that are not strictly your own unless deemed necessary.
