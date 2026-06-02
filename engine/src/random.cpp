#include "random.hpp"
#include <random>
namespace sdlgame::random {
static std::random_device rd;
static std::mt19937 engine = std::mt19937(rd());

int randint(int l, int r) {
  if (l > r)
    std::swap(l, r);
  std::uniform_int_distribution<> tmp(l, r);
  return tmp(engine);
}

/**
 * return a random value between 0 and 1
 */
float randf() {
  std::uniform_real_distribution<> tmp(0, 1);
  return static_cast<float>(tmp(engine));
}
} // namespace sdlgame::random
