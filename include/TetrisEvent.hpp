/**
 * All user event must define here
*/
#ifndef TETRIS_EVENT_HPP
#define TETRIS_EVENT_HPP
#include "engine/engine.hpp"
//just custom user event, all event here is offset from sdlgame::USEREVENT
typedef enum
{
    MERGING = sdlgame::USEREVENT + 1,
    SCORING = sdlgame::USEREVENT + 2,
    GAMEOVER = sdlgame::USEREVENT + 3,
    BUTTON_HOVER = sdlgame::USEREVENT + 4,
    BUTTON_CLICK = sdlgame::USEREVENT + 5,
    ROTATE = sdlgame::USEREVENT + 6,
    SCENETRANS_OUT = sdlgame::USEREVENT + 7,
    SCENETRANS_IN = sdlgame::USEREVENT + 8,
    COUNT_DOWN = sdlgame::USEREVENT + 9,
    COUNT_DOWN_START = sdlgame::USEREVENT + 10,
    SLAM = sdlgame::USEREVENT + 11,
    GAME_PAUSE = sdlgame::USEREVENT + 12,
} Tetris_Event;

#endif