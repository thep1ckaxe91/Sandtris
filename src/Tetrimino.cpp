#include "Tetrimino.hpp"

ShapeInfo::ShapeInfo(uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3,
                     char shape) {
  mask[0] = m0;
  mask[1] = m1;
  mask[2] = m2;
  mask[3] = m3;
  type = shape;
}

Tetrimino::Tetrimino(char shape, SandShift tetriminoColor) : mask(ShapeInfoList.at(shape).mask[0]), type(ShapeInfoList.at(shape).type), color(tetriminoColor) {
}

void Tetrimino::rotate() {
  current_rotation++;
  current_rotation %= 4;
  mask = ShapeInfoList.at(static_cast<char>(type)).mask[current_rotation];
}