#include "Game.h"
#include "Level.h"

Game::Game()
{
    this->levelManager = new LevelManager();
}

Game::~Game()
{
    delete levelManager;
}

void Game::Start()
{
    const int screenWidth = 1300;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Mario & DK Bros");

    SetTargetFPS(60);

    // First screen
    levelManager->LoadLevel(LevelName::startScreen);

    while (!WindowShouldClose())
    {
        this->levelManager->UpdateCurrentLevel();
        this->levelManager->DrawCurrentLevel();
    }

    CloseWindow();
}