#include "Level.h"

Level::Level(LevelType levelType, LevelType nextLevelType, LevelManager& levelManager)
{
	this->levelType = levelType;
    this->nextLevelType = nextLevelType;
    this->levelName = GetLevelName(levelType);
	this->levelManager = &levelManager;

    levelCamera = new LevelCamera();
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

    this->music = LoadMusicStream("../LeProjet/LeProjet/files/audio/SuperMarioBros.mp3");
    this->pause = false;
}

Level::~Level()
{
    UnloadMusicStream(music);
    delete levelCamera;
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
    PlayMusicStream(music);
    pause = false;
}

void Level::UpdateLevel()
{
    UpdateMusicStream(music);
    if (IsKeyPressed(KEY_SEMICOLON))    // Restart music playing
    {
        StopMusicStream(music);
        PlayMusicStream(music);
        pause = false;
    }
    if (IsKeyPressed(KEY_P))    // Pause/Resume music playing
    {
        pause = !pause;

        if (pause) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }
}

void Level::DrawLevel()
{
}

LevelType Level::GetLevelType() const
{
    return levelType;
}

void Level::NextLevel()
{
    this->levelManager->LoadLevel(this->nextLevelType);
}