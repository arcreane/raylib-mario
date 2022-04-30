#pragma once
#include "Player.h"
#include <string>
#include <vector>

class Map
{
private:
	Color backgroundColor;
	std::vector<EnvItem> mapVector;  // vector storing each bloc of the map
	Vector2 startPosition;

	Texture2D Ground;
	Texture2D BlocInconnue;
	Texture2D Bricks;
	Texture2D Dirt;  
	Texture2D Classic;
	Texture2D Pipe;
	Texture2D PipeBas;
	Texture2D Surprise;
	Texture2D Start;
	Texture2D Finish;
	Texture2D Castle;
	Texture2D Poteau;
	Texture2D Flag;
	Texture2D Nuage;
	Texture2D Buisson;
	Texture2D Stone;
	Texture2D Lava;
	Texture2D Bedrock;

public:
	Map();

	void CreateMap(std::string filename);
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
	void DrawMap();

	EnvItem CreateEnvItem(char c,float line, float col);

	Vector2 GetStartPosition() const;
	std::vector<EnvItem> GetMapVector() const;
	void SetMapVector(std::vector<EnvItem> mapVector);
	void SetBackGroundColor(Color backgroundColor);
};

