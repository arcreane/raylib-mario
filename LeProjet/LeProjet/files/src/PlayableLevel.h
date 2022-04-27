#pragma once
#include "Level.h"
#include "Item.h"

class Item;

class PlayableLevel : public Level
{
private:
	std::vector<Item*> itemVector; // vector to store each item of the level
	std::vector<Enemy*> enemies;
	int score;
	int lives;
	bool has_fallen;
	bool gameOver;

	int framesCounter;
	int framesMax;

	Texture2D CoinTexture;
	Texture2D UpMushroomTexture;

	// Enemy functions
	void DrawEnemies();
	void ClearEnemies();
public:
	PlayableLevel(LevelType levelType, LevelType nextLevelType, LevelManager& levelManager);
	~PlayableLevel();
	void InitLevel() override;
	void UpdateLevel() override;
	void DrawLevel() override;

	// Item functions
	void ReadItems(std::string filename);
	Item* CreateItem(char c, float line, float col);
	void DrawItem();
	void RemoveItem(Item* item);
	void ClearItems();

	// Getter Setter
	int GetScore();
	int GetLives();
	void SetScore(int score);
	void SetLives(int lives);

};

