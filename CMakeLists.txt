cmake_minimum_required(VERSION 3.24)

project(Sandtris VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

# Sanitizer configuration for Lab builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(engine)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Sandtris ${SOURCE_FILES})

# The "Gauntlet" - Strict warnings for high-performance systems
target_compile_options(Sandtris PRIVATE 
    -Wall 
    -Wextra 
    -Wconversion 
    -Wshadow 
    -Wpedantic
    # -Werror
)

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
