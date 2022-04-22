#pragma once
#include "Player.h"
#include <string>
#include <vector>


class Map
{
public:
	Color backgroundColor;
	std::vector<EnvItem> mapVector;  // vectore to store each map bloc

	Texture2D Ground;
	Texture2D BlocInconnue;
	Texture2D Start;
	Texture2D Finish;
	
	Map();
	void CreateMap(std::string filename);
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
	void DrawMap();

	EnvItem CreateEnvItem(char c,float line, float col);
};

