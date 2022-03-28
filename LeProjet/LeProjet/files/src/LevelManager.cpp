#include "LevelManager.h"

void LevelManager::LoadLevel(LevelName name)
{
	bool levelFound = false;

	for (int i = 0; i < levels.size(); i++)
	{
		if (levels[i].name == name)
		{
			currentLevel = levels[i];
			levelFound = true;
			break;
		}
	}
	
	if (!levelFound)
	{
		Level newLevel = Level(name);
		levels.push_back(newLevel);
		currentLevel = newLevel;
	}

}
