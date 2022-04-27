#include "Level.h"

Level::Level(LevelType levelType, LevelType nextLevelType, LevelManager& levelManager)
{
	this->levelType = levelType;
    this->nextLevelType = nextLevelType;
    this->levelName = GetLevelName(levelType);
	this->levelManager = &levelManager;

	camera = { 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	cameraOption = 0;

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();
}

std::string Level::GetLevelName(LevelType levelType)
{
    switch (levelType)
    {
    case LevelType::startScreen:
        return "Ecran d'accueil";
    case LevelType::characterScreen:
        return "Ecran d'utilisateur";
    case LevelType::menu:
        return "Menu";
    case LevelType::lvl1:
        return "Niveau 1";
    case LevelType::lvl2:
        return "Niveau 2";
    case LevelType::lvl3:
        return "Niveau 3";
    case LevelType::lvl4:
        return "Niveau 4";
    case LevelType::lvl5:
        return "Niveau 5";
    case LevelType::lvl6:
        return "Niveau 6";
    default:
        return "Niveau ?";
    }
}

void Level::InitLevel()
{
    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    player.InitPlayer();
}

void Level::UpdateLevel()
{
}

void Level::DrawLevel()
{
}

void Level::NextLevel()
{
    this->levelManager->LoadLevel(this->nextLevelType);
}