#pragma once
#include "LevelManager.h"
#include "Map.h"

enum class LevelName { startScreen, characterScreen, menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class LevelManager;

class Level
{
public:
	LevelName name;
	LevelManager *levelManager;
	Map map;
	Player player;

	Camera2D camera;
	int cameraOption;
	int screenWidth;
	int screenHeight;

	int framesCounter;
	int framesMax;

	//ENEMY à classer
	int enemyAmount;
	std::vector<Enemy> goomba;
	std::vector<Enemy> koopa;
	double previousTime;
	double currentTime;
	float deltaTime;
	double previousTime2;
	double currentTime2;
	float deltaTime2;
	std::string direction;
	std::string direction2;

	Texture2D marioTexture;
	Texture2D goombaTexture;
	Texture2D goombaTexture2;
	Texture2D koopaTexture;
	Texture2D koopaTexture2;

	Level(LevelName name, LevelManager &levelManager);

	virtual void InitLevel();
	virtual void UpdateLevel();
	virtual void DrawLevel();
};

