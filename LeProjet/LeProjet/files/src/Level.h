#pragma once
#include <string>
#include "Player.h"
#include "LevelManager.h"
#include "Map.h"
#include "Item.h"


enum class LevelName { startScreen, characterScreen, menu, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6 };
class Player;
class LevelManager;
class Item;

class Level
{
public:
	LevelName name;
	LevelName nextLevelName;
	LevelManager *levelManager;
	Map map;
	std::vector<Item*> itemVector; // vector to store each item of the level
	Player player;
	int score;
	int lives;
	std::string nameDisplayed;

	// Item textures
	Texture2D CoinTexture;
	Texture2D UpMushroomTexture;

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

	Level(LevelName name, LevelName nextLevelName, LevelManager &levelManager, std::string nameDisplayed);
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

	void NextLevel();
};

