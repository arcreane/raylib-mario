#pragma once
#include "Player.h"
#include <string>
#include <vector>
#include "Item.h"

class Map
{
public:
	Color backgroundColor;

	std::vector<EnvItem> mapVector;  // vectore to store each map bloc
	std::vector<Item> itemVector; // vector to store each item

	void ReadItems(std::string filename);
	Item CreateItem(char c, float line, float col);
	void DrawItem();

	void CreateMap(std::string filename);
	EnvItem CreateEnvItem(char c,float line, float col);
	void DrawMap();
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
};

