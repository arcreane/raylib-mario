#pragma once
#include "Player.h"
#include <string>
#include <vector>

class Map
{
public:
	Color backgroundColor;

	std::vector<EnvItem> mapVector;  // array to store each line
	void CreateMap(std::string filename);
	EnvItem CreateEnvItem(char c,float line, float col);
	void DrawMap();
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
};

