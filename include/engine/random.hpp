#ifndef SDLGAME_RANDOM_
#define SDLGAME_RANDOM_
#include <bits/stdc++.h>
namespace sdlgame {
    namespace random
    {
        extern std::random_device rd;
        extern std::mt19937 engine;
        /*
         * return a random interger in range [l,r], if l > r, it automatically swap
         * the range can be up to 2^30
         */
        int randint(int l, int r);

        /**
         * return a random value between 0 and 1
         */
        float randf();
    }
}

#endif