cmake_minimum_required(VERSION 3.16)

project(Sandtris VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include to allow Cross Platform Compilation
include(FetchContent)

find_package(SDL2 QUIET)

if(SDL2_FOUND)
    message(STATUS "Found installed SDL2. Using system version.")
else()
    # download and build if not found
    message(STATUS "SDL2 not found. Fetching from GitHub...")
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5  # pin the version for stability
    )
    FetchContent_MakeAvailable(SDL2)
endif()

find_package(SDL2_image QUIET)
if(NOT SDL2_image_FOUND)
    message(STATUS "SDL2_image not found. Fetching...")
    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.0
    )
    FetchContent_MakeAvailable(SDL2_image)
endif()

find_package(SDL2_mixer QUIET)
if(NOT SDL2_mixer_FOUND)
    message(STATUS "SDL2_mixer not found. Fetching...")
    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0
    )
    FetchContent_MakeAvailable(SDL2_mixer)
endif()

find_package(SDL2_ttf QUIET)
if(NOT SDL2_ttf_FOUND)
    message(STATUS "SDL2_mixer not found. Fetching...")
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.24.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)
endif()


add_subdirectory(engine)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Sandtris ${SOURCE_FILES})

# linking stage, since we use fetch, the name might differ
target_link_libraries(Sandtris PRIVATE GameEngine)


target_include_directories(Sandtris PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_custom_command(TARGET Sandtris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Sandtris>/assets
    COMMENT "Copying assets..."
)