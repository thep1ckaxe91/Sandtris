# src/engine/CMakeLists.txt

# Gather all engine source files
file(GLOB ENGINE_SOURCES "*.cpp")

# Define a library for the engine. 
# It can be STATIC (compiled into your executable) or SHARED (a separate .dll or .so file).
# STATIC is simpler to start with.
add_library(GameEngine STATIC ${ENGINE_SOURCES})

# Make sure the engine can find its own header files in the `include` directory
target_include_directories(GameEngine PUBLIC ../../include PRIVATE ../../include/engine)
