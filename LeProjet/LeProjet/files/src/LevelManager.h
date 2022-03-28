#pragma once
#include "Level.h"
#include <vector>

class LevelManager
{
public:
	Level currentLevel;
	std::vector<Level> levels;
	void LoadLevel(LevelName name);
};

