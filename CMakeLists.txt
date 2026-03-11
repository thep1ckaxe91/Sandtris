cmake_minimum_required(VERSION 3.24)

project(Sandtris VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image  REQUIRED CONFIG)
find_package(SDL2_mixer  REQUIRED CONFIG)
find_package(SDL2_ttf  REQUIRED CONFIG)

add_subdirectory(engine)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(Sandtris ${SOURCE_FILES})

target_compile_options(Sandtris PRIVATE -fno-omit-frame-pointer)

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