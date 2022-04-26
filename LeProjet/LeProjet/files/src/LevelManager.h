#pragma once
#include "Level.h"
#include <vector>

class Level;
enum class LevelName;

class LevelManager
{
private:
	int indexCurrentLevel;
	std::vector<Level*> levels;
	Level* CreateLevel(LevelName name);

public:
	~LevelManager();

	void LoadLevel(LevelName name);
	/*void LoadMenuFromLvl(LevelName name, char* playerName);*/
	void UpdateCurrentLevel();
	void DrawCurrentLevel();

	Level getCurrentLevel();
};

