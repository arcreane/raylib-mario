#pragma once
#include <string>
#include "Player.h"
#include "LevelManager.h"
#include "Map.h"
#include "Item.h"
#include "Enemy.h"


enum class LevelType { startScreen, characterScreen, menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class Player;
class LevelManager;
class Item;

class Level
{
public:
	LevelType levelType;
	LevelType nextLevelType;
	LevelManager *levelManager;
	Map map;
	std::vector<Item*> itemVector; // vector to store each item of the level
	std::vector<Enemy*> enemies;
	Player player;
	std::string nameDisplayed;
	int score;
	int lives;
	bool has_fallen;
	bool gameOver;

	// Item textures
	Texture2D CoinTexture;
	Texture2D UpMushroomTexture;

	Camera2D camera;
	int cameraOption;
	int screenWidth;
	int screenHeight;

	int framesCounter;
	int framesMax;

	Level(LevelType levelType, LevelType nextLevelType, LevelManager &levelManager, std::string nameDisplayed);
	~Level();

	virtual void InitLevel();
	virtual void UpdateLevel();
	virtual void DrawLevel();

	// Item functions
	void ReadItems(std::string filename);
	Item* CreateItem(char c, float line, float col);
	void DrawItem();
	void RemoveItem(Item *item);
	void ClearItems();
protected:
	// Enemy functions
	void DrawEnemies();
	void ClearEnemies();

	virtual void NextLevel();
};

