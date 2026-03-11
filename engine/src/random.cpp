#include "random.hpp"
#include <random>
namespace sdlgame::random {
std::random_device rd;
std::mt19937 engine = std::mt19937(rd());

int randint(int l, int r) {
  if (l > r)
    std::swap(l, r);
  std::uniform_int_distribution<> tmp(l, r);
  return tmp(engine);
}

/**
 * return a random value between 0 and 1
 */
float randf() { return randint(0, 1000000) / 1000000.0; }
} // namespace sdlgame::random
