#include "LevelManager.h"
#include "Menu.h"
#include "StartScreen.h"
#include "CharacterScreen.h"

Level* LevelManager::CreateLevel(LevelName name)
{
	Level* newLevel;
	switch (name)
	{
	case LevelName::startScreen:
		newLevel = new StartScreen(*this);
		break;
	case LevelName::characterScreen:
		newLevel = new CharacterScreen(*this);
		break;
	case LevelName::menu:
		newLevel = new Menu(*this);
		break;
	case LevelName::lvl1:
		newLevel = new Level(name, LevelName::lvl2, *this, "Niveau 1");
		break;
	case LevelName::lvl2:
		newLevel = new Level(name, LevelName::lvl3, *this, "Niveau 2");
		break;
	case LevelName::lvl3:
		newLevel = new Level(name, LevelName::lvl4, *this, "Niveau 3");
		break;
	case LevelName::lvl4:
		newLevel = new Level(name, LevelName::lvl5, *this, "Niveau 4");
		break;
	case LevelName::lvl5:
		newLevel = new Level(name, LevelName::lvl6, *this, "Niveau 5");
		break;
	case LevelName::lvl6:
		newLevel = new Level(name, LevelName::menu, *this, "Niveau 6");
		break;
	default:
		newLevel = new Level(name, LevelName::menu, *this, "Niveau ?");
	}

	return newLevel;
}

void LevelManager::LoadLevel(LevelName name)
{
	bool levelFound = false;

	for (int i = 0; i < levels.size(); i++)
	{
		if ((*levels[i]).name == name)
		{
			indexCurrentLevel = i;
			levelFound = true;
			break;
		}
	}
	
	if (!levelFound)
	{
		Level* newLevel = CreateLevel(name);
		levels.push_back(newLevel);
		indexCurrentLevel = levels.size() - 1;
	}

	(*levels[indexCurrentLevel]).InitLevel();
}

/*void LevelManager::LoadMenuFromLvl(LevelName name, char* playerName)
{
	bool levelFound = false;

	for (int i = 0; i < levels.size(); i++)
	{
		if ((*levels[i]).name == name)
		{
			indexCurrentLevel = i;
			levelFound = true;
			break;
		}
	}

	if (!levelFound)
	{
		Level* newLevel = new Menu(*this, playerName);
		levels.push_back(newLevel);
		indexCurrentLevel = levels.size() - 1;
	}

	(*levels[indexCurrentLevel]).InitLevel();
}*/

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
