#pragma once
#include "Level.h"
#include "Item.h"
#include "Enemy.h"

class Item;
class Enemy;

class PlayableLevel : public Level
{
private:
	std::vector<Item*> itemVector; // vector to store each item of the level
	std::vector<Enemy*> enemies;
	int score;
	bool has_fallen;
	bool gameOver;

	int framesCounter;
	int framesMax;

	// Item functions
	void ReadItems(std::string filename);
	Item* CreateItem(char c, float line, float col);
	void DrawItems();
	void ClearItems();

	// Enemy functions
	void DrawEnemies();
	void ClearEnemies();
	
public:
	PlayableLevel(LevelType levelType, LevelType nextLevelType, LevelManager& levelManager);
	~PlayableLevel();

	void InitLevel() override;
	void UpdateLevel() override;
	void DrawLevel() override;

	void SaveAfterLevelFinished();
	void RespawnPlayer();
	void RemoveItem(Item* item);
	void RemoveEnemy(Enemy* enemy);
	
	// Getter Setter
	int GetScore();
	void SetScore(int score);
};

