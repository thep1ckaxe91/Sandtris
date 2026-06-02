# Sandtris: Refactor for Performance - Technical Guide

## 1. Project Objective

The primary goal of this project is to refactor the Sandtris game to significantly improve its performance and scalability, allowing it to simulate a much larger number of sand particles at a higher resolution. The project has been modernized to use C++23 and a robust dependency management system.

## 2. Game Architecture

The project is structured into two main components:

### 2.1. Game Engine (`engine/`)
A custom C++ engine that wraps SDL2, providing a Pygame-inspired API.
*   **Location:** `/engine`
*   **Source:** `/engine/src`
*   **Headers:** `/engine/include`
*   **Build:** Compiled as a static library `GameEngine`.
*   **Optimization:** Uses aggressive compiler flags (`-O3`, `-ftree-vectorize`, `-march=native`) in Release/RelWithDebInfo modes for SIMD and performance.

### 2.2. Game Logic (`src/`)
Contains the Sandtris-specific implementation.
*   **Source:** `/src`
*   **Headers:** `/include`
*   **Simulation:** Focuses on high-performance sand physics and efficient rendering.

## 3. Build System & Dependency Management

### 3.1. Conan 2.0
The project uses **Conan** as its primary package manager. 
*   **Config:** `conanfile.py`
*   **Dependencies:** SDL2 (2.32.10), SDL2_ttf, SDL2_image, SDL2_mixer, Protobuf, and GTest.
*   **Integration:** Conan generates CMake toolchain and dependency files, which are used by CMake to locate and link libraries.

### 3.2. CMake
The build is orchestrated by CMake (minimum version 3.24).
*   **Root `CMakeLists.txt`:** Manages the main executable and assets.
*   **`engine/CMakeLists.txt`:** Manages the engine library and its specific optimizations.
*   **Modern Practices:** Uses target-based linking and explicit include directories.

## 4. Build and Run Instructions

1.  **Install Dependencies (Conan):**
    ```bash
    conan install . --output-folder=build --build=missing
    ```
2.  **Configure and Build:**
    ```bash
    ./cmake_build.sh
    ```
    *(The script typically handles CMake configuration and building using the Conan toolchain.)*

---

## 5. Evaluation of Current Setup (Conan + CMake)

### 5.1. Pros
*   **Reliable Dependency Management:** Conan handles the complex tree of SDL2 dependencies (Ogg, Vorbis, etc.) automatically, ensuring binary compatibility and correct linking.
*   **Modern C++ Standards:** The use of C++23 allows for the latest language features, and CMake 3.24+ integration provides a smoother experience with Conan 2.0.
*   **Build Speed:** Once dependencies are installed by Conan, they are cached. Rebuilding the project only recompiles the game and engine source code.
*   **Clean Source Tree:** No need for a `vendored/` folder, keeping the repository lean and focused on project-specific code.

### 5.2. Cons
*   **Configuration Complexity:** The `conanfile.py` and CMake integration can be complex to set up initially, especially with target aliasing and custom flags.
*   **Developer Onboarding:** Requires developers to have Conan 2.0 installed and configured on their system.
*   **Hidden Magic:** Issues within the Conan-generated files can sometimes be harder to debug than manual `add_subdirectory` calls.

### 5.3. Potential Improvements
*   **Full CMake Integration:** Instead of a separate `cmake_build.sh`, the Conan installation can be integrated directly into the CMake configure step using `conan_cmake_run` (though the current approach is often more robust).
*   **Binary Caching:** Using a remote Conan server (like Artifactory) would allow the team to share pre-compiled binaries for the engine itself.
*   **Testing Integration:** Ensure `GTest` is fully integrated into the CMake test runner (`ctest`) for automated validation of physics logic.

---

## 6. Architecture Mandates

*   **SDL Version:** SDL2 (via Conan).
*   **Standards:** C++23.
*   **Optimizations:** Explicit SIMD and tree vectorization in the engine.
*   **Memory:** RAII compliance. No raw `new/delete` in game logic.
