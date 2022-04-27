#pragma once
#include <string>
#include "Player.h"
#include "LevelManager.h"
#include "Map.h"
#include "Enemy.h"


enum class LevelType { startScreen, characterScreen, menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class Player;
class LevelManager;

class Level
{
public:
	LevelType levelType;
	LevelType nextLevelType;
	std::string levelName;
	LevelManager *levelManager;
	Map map;
	Player player;

	Camera2D camera;
	int cameraOption;
	int screenWidth;
	int screenHeight;

	Level(LevelType levelType, LevelType nextLevelType, LevelManager &levelManager);
	std::string GetLevelName(LevelType levelType);

	virtual void InitLevel();
	virtual void UpdateLevel();
	virtual void DrawLevel();

protected:
	virtual void NextLevel();
};

