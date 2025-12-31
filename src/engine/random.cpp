#include "random.hpp"
#include <chrono>
#include <random>
namespace sdlgame
{
    namespace random
    {
        std::random_device rd;
        std::mt19937 engine = std::mt19937(rd());
    }
}
int sdlgame::random::randint(int l, int r)
{
    if (l > r)
        std::swap(l, r);
    std::uniform_int_distribution<> tmp(l, r);
    return tmp(engine);
}

/**
 * return a random value between 0 and 1
 */
float sdlgame::random::randf()
{
    return randint(0, 1000000) / 1000000.0;
}