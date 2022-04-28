#pragma once
#include "Level.h"
#include <vector>

class Level;
enum class LevelType;
class PlayableLevel;

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

