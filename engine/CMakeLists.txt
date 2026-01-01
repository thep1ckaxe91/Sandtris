file(GLOB ENGINE_SOURCES "src/*.cpp")


add_library(GameEngine STATIC ${ENGINE_SOURCES})

# public here mean any unit which link this lib will able to access the header in /include
target_include_directories(GameEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# assume the unit which use this already found SDL2 and its extends in someway, we use it directly
# NOTE: this only works if the ret is actually SDL2::SDL2 and not SDL2, so might need change later on
target_link_libraries(GameEngine PRIVATE 
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)