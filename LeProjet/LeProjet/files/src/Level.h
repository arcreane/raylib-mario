#pragma once
#include <string>
#include "Player.h"
#include "LevelManager.h"
#include "Map.h"
#include "LevelCamera.h"
#include "raylib.h"

enum class LevelType { startScreen, characterScreen, menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class Player;
class LevelManager;

class Level
{
protected:
	LevelType levelType;
	LevelType nextLevelType;
	std::string levelName;
	LevelManager* levelManager;
	Map map;
	Player player;

	LevelCamera* levelCamera;
	int screenWidth;
	int screenHeight;

	Music music;
	bool pause;

	virtual void NextLevel();

public:
	Level(LevelType levelType, LevelType nextLevelType, LevelManager &levelManager);
	~Level();

	virtual void InitLevel();
	virtual void UpdateLevel();
	virtual void DrawLevel();

	std::string GetLevelName(LevelType levelType);
	LevelType GetLevelType() const;
};

