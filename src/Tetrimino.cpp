#include "Tetrimino.hpp"

ShapeInfo::ShapeInfo(uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3, char shape) {
    mask[0] = m0;
    mask[1] = m1;
    mask[2] = m2;
    mask[3] = m3;
    type = shape;
}
Tetrimino::Tetrimino(char shape, SandShift color)
{
    type = shape;
    color = color;
    mask =  ShapeInfoList.at(type).mask[0];
}
Tetrimino::Tetrimino()=default;

void Tetrimino::rotate()
{
    current_rotation++;
    current_rotation%=4;
    mask = ShapeInfoList.at(type).mask[current_rotation];
}