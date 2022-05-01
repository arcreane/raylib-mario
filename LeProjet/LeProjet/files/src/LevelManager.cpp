#include "LevelManager.h"
#include "Menu.h"
#include "StartScreen.h"
#include "CharacterScreen.h"
#include "PlayableLevel.h"

Level* LevelManager::CreateLevel(LevelType levelType)
{
	Level* newLevel;
	switch (levelType)
	{
	case LevelType::startScreen:
		newLevel = new StartScreen(*this);
		break;
	case LevelType::characterScreen:
		newLevel = new CharacterScreen(*this);
		break;
	case LevelType::menu:
		newLevel = new Menu(*this);
		break;
	case LevelType::lvl1:
		newLevel = new PlayableLevel(levelType, LevelType::lvl2, *this);
		break;
	case LevelType::lvl2:
		newLevel = new PlayableLevel(levelType, LevelType::lvl3, *this);
		break;
	case LevelType::lvl3:
		newLevel = new PlayableLevel(levelType, LevelType::lvl4, *this);
		break;
	case LevelType::lvl4:
		newLevel = new PlayableLevel(levelType, LevelType::lvl5, *this);
		break;
	case LevelType::lvl5:
		newLevel = new PlayableLevel(levelType, LevelType::lvl6, *this);
		break;
	case LevelType::lvl6:
		newLevel = new PlayableLevel(levelType, LevelType::menu, *this);
		break;
	default:
		newLevel = new PlayableLevel(levelType, LevelType::menu, *this);
	}

	return newLevel;
}

void LevelManager::LoadLevel(LevelType levelType)
{
	bool levelFound = false;
	
	// Check if the level is in the vectot of levels
	for (int i = 0; i < levels.size(); i++)
	{
		if ((*levels[i]).GetLevelType() == levelType)
		{
			indexCurrentLevel = i;
			levelFound = true;
			break;
		}
	}
	
	// If the level is not in the vector of levels we create the level and add it to the vector
	if (!levelFound)
	{
		Level* newLevel = CreateLevel(levelType);
		levels.push_back(newLevel);
		indexCurrentLevel = levels.size() - 1;
	}

	(*levels[indexCurrentLevel]).InitLevel();
}

void LevelManager::UpdateCurrentLevel()
{
	(*levels[indexCurrentLevel]).UpdateLevel();
}

void LevelManager::DrawCurrentLevel()
{
	(*levels[indexCurrentLevel]).DrawLevel();
}

Level LevelManager::getCurrentLevel()
{
	return *levels[indexCurrentLevel];
}

LevelManager::~LevelManager()
{
	for (int i = 0; i < levels.size(); i++)
	{
		delete levels[i];
	}
}
