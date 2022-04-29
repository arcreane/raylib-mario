#pragma once
#include "Level.h"
#include <vector>

enum class LevelType;
class Level;

class LevelManager
{
private:
	int indexCurrentLevel;
	std::vector<Level*> levels;
	Level* CreateLevel(LevelType levelType);

public:
	~LevelManager();

	void LoadLevel(LevelType levelType);
	void UpdateCurrentLevel();
	void DrawCurrentLevel();

	Level getCurrentLevel();
};

