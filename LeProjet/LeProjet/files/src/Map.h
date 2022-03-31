#pragma once
#include "Player.h"
#include "Item.h"
#include <string>
#include <vector>


class Map
{
public:
	Color backgroundColor;
	std::vector<EnvItem> mapVector;  // vectore to store each map bloc
	std::vector<Item> itemVector; // vector to store each item

	Texture2D Ground;
	Texture2D BlocInconnue;
	Texture2D Start;
	Texture2D Finish;

	// TODO : Move in corresponding Level 
	Texture2D CoinTexture;
	Texture2D ShroomTexture;
	
	Map();
	void CreateMap(std::string filename);
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
	void DrawMap();

	EnvItem CreateEnvItem(char c,float line, float col);

	// TODO : Move in corresponding Level 
	void ReadItems(std::string filename);
	Item CreateItem(char c, float line, float col);
	void DrawItem();
};

