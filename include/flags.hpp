/**
 * @file flags.hpp
 * @author your name (you@domain.com)
 * @copyright Copyright (c) 2024
 * 
 * Mostly use to terminate thread if user press alt + f4
 */
#ifndef FLAGS_HPP
#define FLAGS_HPP
#include <atomic>
extern std::atomic<int> game_ended;

#endif