# Stuff learned
## Dependencies 
### Step 1: Declare the Dependency in Conan

Conan is the source of truth for packages. You must first register the dependency in  conanfile.py  under the  requires  list.
      requires = [
              "protobuf/6.32.1",
              "gtest/1.17.0",
              "sdl/2.32.10",
              "sdl_ttf/2.24.0",
              "sdl_image/2.8.8",
              "sdl_mixer/2.8.1",
              "cpptrace/1.0.4" # <-- Added here
          ]

### Step 2: Bind the Package in CMake
Conan downloads the library and generates configuration files, but CMake needs to be explicitly told to consume them. In the root CMakeLists.txt, use  find_package :

  find_package(SDL2_mixer REQUIRED CONFIG)
  find_package(SDL2_ttf REQUIRED CONFIG)
  find_package(cpptrace REQUIRED) # <-- Added here

### Step 3: Link to the Specific Target

You must link the imported target to the actual compiled binaries that require it. For  cpptrace , this goes into CMakeLists.txt under the  GameEngine  target. The standard Conan target naming convention is
PackageName::PackageName .

  target_link_libraries(GameEngine PRIVATE
      SDL2::SDL2
      SDL2_image::SDL2_image
      SDL2_ttf::SDL2_ttf
      SDL2_mixer::SDL2_mixer
      cpptrace::cpptrace # <-- Added here
  )

### Step 4: Purge, Configure, and Build

This is where most people fail. You cannot just run  cmake --build  after altering  conanfile.py . You must regenerate the toolchain constraints and clear out old configurations, or CMake will throw duplicate
preset errors.

Run these commands in this exact sequence:

1. Purge stale generated presets to prevent cache poisoning
```
rm -f CMakeUserPresets.json build/CMakeUserPresets.json
```

2. Leverage Conan to fetch the package and regenerate the CMake toolchain
```
conan install . --output-folder=build --build=missing -s build_type=RelWithDebInfo
```

3. Re-configure the CMake project mapping
```
cmake --preset conan-relwithdebinfo
```

4. Compile the binaries
```
cmake --build --preset conan-relwithdebinfo --parallel $(nproc)
```
