#pragma once
#ifndef SDLGAME_RANDOM_
#define SDLGAME_RANDOM_


namespace sdlgame::random {
/*
 * return a random interger in range [l,r], if l > r, it automatically swap
 * the range can be up to 2^30
 */
int randint(int l, int r);

/**
 * return a random value between 0 and 1
 */
float randf();
} // namespace sdlgame::random

#endif