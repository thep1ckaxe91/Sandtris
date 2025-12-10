cmake_minimum_required(VERSION 3.16)

project(Sandtris VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(SOURCE_FILES
    src/main.cpp
    src/Animation.cpp
    src/AudioManager.cpp
    src/BackButton.cpp
    src/Button.cpp
    src/Credit.cpp
    src/CreditButton.cpp
    src/flags.cpp
    src/Game.cpp
    src/GameOver.cpp
    src/GamePlay.cpp
    src/Grid.cpp
    src/HowToPlay.cpp
    src/HTPButton.cpp
    src/Images.cpp
    src/MainMenu.cpp
    src/MenuButton.cpp
    src/Option.cpp
    src/OptionButton.cpp
    src/OptionElement.cpp
    src/Pause.cpp
    src/PauseButton.cpp
    src/PBButton.cpp
    src/PersonalBest.cpp
    src/QuitButton.cpp
    src/ResumeButton.cpp
    src/RetryButton.cpp
    src/Sand.cpp
    src/SaveData.cpp
    src/scene_transitions.cpp
    src/Scene.cpp
    src/SceneTransition.cpp
    src/SFX.cpp
    src/Slider.cpp
    src/splash_screens.cpp
    src/SplashScreen.cpp
    src/StartButton.cpp
    src/State.cpp
    src/Tetrimino.cpp
    src/TetriminoController.cpp
    src/tetriminoes.cpp
    src/engine/color.cpp
    src/engine/display.cpp
    src/engine/draw.cpp
    src/engine/engine.cpp
    src/engine/event.cpp
    src/engine/font.cpp
    src/engine/image.cpp
    src/engine/key.cpp
    src/engine/math.cpp
    src/engine/mixer.cpp
    src/engine/mouse.cpp
    src/engine/music.cpp
    src/engine/random.cpp
    src/engine/rect.cpp
    src/engine/sprite.cpp
    src/engine/surface.cpp
    src/engine/time.cpp
    src/engine/transform.cpp
)

include_directories(
    include/
)

add_executable(Sandtris ${SOURCE_FILES})

target_link_libraries(Sandtris PRIVATE SDL3::SDL3)

add_custom_command(TARGET Sandtris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Sandtris>/assets
)