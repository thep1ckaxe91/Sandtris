#include "tetriminoes.hpp"

namespace Tetriminoes {
// Return a random color I tetrimino
Tetrimino I() {
  return Tetrimino('I', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color O tetrimino
Tetrimino O() {
  return Tetrimino('O', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color T tetrimino
Tetrimino T() {
  return Tetrimino('T', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color S tetrimino
Tetrimino S() {
  return Tetrimino('S', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color Z tetrimino
Tetrimino Z() {
  return Tetrimino('Z', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color J tetrimino
Tetrimino J() {
  return Tetrimino('J', SandShift(1 << sdlgame::random::randint(0, 3)));
}
// Return a random color L tetrimino
Tetrimino L() {
  return Tetrimino('L', SandShift(1 << sdlgame::random::randint(0, 3)));
}
Tetrimino randomTetrimino() {
  int r_num = sdlgame::random::randint(1, 7);
  switch (r_num) {
  case 1:
    return I();
    break;
  case 2:
    return O();
    break;
  case 3:
    return T();
    break;
  case 4:
    return S();
    break;
  case 5:
    return Z();
    break;
  case 6:
    return J();
    break;
  default:
    return L();
    break;
  }
}
} // namespace Tetriminoes