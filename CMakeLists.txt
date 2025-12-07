cmake_minimum_required(VERSION 3.16)

project(Sandtris VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Ensure standard compliance

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(SOURCE_FILES
    src/main.cpp
    src/engine/Renderer.cpp
    # Add your scene files here
)

add_executable(Sandtris ${SOURCE_FILES})

target_link_libraries(Sandtris PRIVATE SDL3::SDL3)

add_custom_command(TARGET Sandtris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Sandtris>/assets
)