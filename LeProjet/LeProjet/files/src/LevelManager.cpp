#include "LevelManager.h"
#include "Menu.h"
#include "StartScreen.h"
#include "CharacterScreen.h"

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
		newLevel = new Level(levelType, LevelType::lvl2, *this, "Niveau 1");
		break;
	case LevelType::lvl2:
		newLevel = new Level(levelType, LevelType::lvl3, *this, "Niveau 2");
		break;
	case LevelType::lvl3:
		newLevel = new Level(levelType, LevelType::lvl4, *this, "Niveau 3");
		break;
	case LevelType::lvl4:
		newLevel = new Level(levelType, LevelType::lvl5, *this, "Niveau 4");
		break;
	case LevelType::lvl5:
		newLevel = new Level(levelType, LevelType::lvl6, *this, "Niveau 5");
		break;
	case LevelType::lvl6:
		newLevel = new Level(levelType, LevelType::menu, *this, "Niveau 6");
		break;
	default:
		newLevel = new Level(levelType, LevelType::menu, *this, "Niveau ?");
	}

	return newLevel;
}

void LevelManager::LoadLevel(LevelType levelType)
{
	bool levelFound = false;

	for (int i = 0; i < levels.size(); i++)
	{
		if ((*levels[i]).levelType == levelType)
		{
			indexCurrentLevel = i;
			levelFound = true;
			break;
		}
	}
	
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
