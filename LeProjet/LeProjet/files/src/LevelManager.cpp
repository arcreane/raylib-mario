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
		newLevel = new Level(name, *this);
		break;
	default:
		newLevel = new Level(name, *this);
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
