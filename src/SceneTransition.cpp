// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "SceneTransition.hpp"


SceneTransition::SceneTransition(double time){this->time = time; this->isDone = 0;}
SceneTransition::~SceneTransition() = default;