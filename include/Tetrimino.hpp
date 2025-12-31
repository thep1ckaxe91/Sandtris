#ifndef TETRIMINO_HPP
#define TETRIMINO_HPP
#include "Sand.hpp"
#include "engine/engine.hpp"
using namespace std;
typedef struct ShapeInfo {
    uint16_t mask[4];
    char type;

    ShapeInfo(uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3, char shape);
} ShapeInfo;
const ShapeInfo I_info={
    0xf0,
    0x2222,
    0xf0,
    0x2222,
    'I'
};
const ShapeInfo O_info={
    0x660,
    0x660,
    0x660,
    0x660,
    'O'
};
const ShapeInfo T_info={
    0xe40,
    0x4c40,
    0x4e00,
    0x4640,
    'T'
};
const ShapeInfo S_info={
    0x6c0,
    0x4620,
    0x6c0,
    0x4620,
    'S'
};
const ShapeInfo Z_info={
    0xc60,
    0x2640,
    0xc60,
    0x2640,
    'Z'
};
const ShapeInfo J_info={
    0xe20,
    0x44c0,
    0x8e00,
    0x6440,
    'J'
};
const ShapeInfo L_info={
    0xe80,
    0xc440,
    0x2e00,
    0x4460,
    'L'
};
const map<char,ShapeInfo> ShapeInfoList = {
    {'I', I_info},
    {'O', O_info},
    {'T', T_info},
    {'S', S_info},
    {'Z', Z_info},
    {'J', J_info},
    {'L', L_info}
};

/**
 * When a Tetrimino falling, it not appear in the grid yet,
 * it appear differenctly and control by Tetrimino Controller
*/
struct Tetrimino
{
    SandShift color;
    /**
     * 1 bit is for 1 cell, 
     * 1 mean there are thing to draw, 0 mean no 
     * for better image, this is the T shape :
     * 0100
     * 1100
     * 0100
     * 0000
     * =0100 1100 0100 0000
     * =0x4c40
    */
    Uint16 mask;
    char type;
    Uint8 current_rotation = 0;
    /**
     * @param shape the character stand for the shape
     * @param color SandShift color for the shape
    */
    Tetrimino(char shape, SandShift color);
    Tetrimino();

    void rotate();
};

#endif