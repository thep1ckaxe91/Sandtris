// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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