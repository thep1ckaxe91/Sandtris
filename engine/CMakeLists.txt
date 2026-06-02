file(GLOB ENGINE_SOURCES "src/*.cpp")

add_library(GameEngine STATIC ${ENGINE_SOURCES})

# public here mean any unit which link this lib will able to access the header in /include
target_include_directories(GameEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# assume the unit which use this already found SDL2 and its extends in someway, we use it directly
target_link_libraries(GameEngine PRIVATE 
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)

# this was generated in an attempt for compiler optimization for SIMD
target_compile_options(GameEngine PRIVATE
    -Wall 
    -Wextra 
    -Wconversion 
    -Wshadow 
    -Wpedantic
    $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:
        -O3
        -ftree-vectorize 
        -march=native 
    >
    
    # Optional: Apply basic optimizations during Debug to keep the engine playable, 
    # but keep debug symbols fully intact. 
    $<$<CONFIG:Debug>:
        -O0 
        -g3
    >
)
