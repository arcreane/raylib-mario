#pragma once
#include "Map.h"

enum class LevelName { menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class Level
{
public:
	Map map;
	LevelName name;
	Level(LevelName name);
	void CreateMenu();
	void CreateLevel(std::string filename);

};

