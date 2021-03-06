#include "StartScreen.h"

StartScreen::StartScreen(LevelManager& levelManager)
	:Level(LevelType::startScreen, LevelType::menu, levelManager)
{
    currentScreen = GameMoment::DEBUT;
    frameHeight = (float)playButtonTexture.height;
    positionClick = { 0.0f, 0.0f };
    backgroundTexture = LoadTexture("../LeProjet/LeProjet/files/img/ecran11.png");
	playButtonTexture = LoadTexture("../LeProjet/LeProjet/files/img/play.png");
}

void StartScreen::InitLevel()
{
}

void StartScreen::UpdateLevel()
{
    switch (currentScreen)
    {
    case GameMoment::DEBUT:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
        {
            currentScreen = GameMoment::CREERREPRENDRE;
        }
        break;
    case GameMoment::CREERREPRENDRE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            positionClick = GetMousePosition();
            if (positionClick.x < 650)
            {
                // Load an existing game save
                levelManager->LoadLevel(LevelType::menu);
            }
            else
            {
                
                // Create a new game save
                levelManager->LoadLevel(LevelType::characterScreen);
            }
        }
        break;
    default:
        break;
    }
}

void StartScreen::DrawLevel()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen)
    {
    case GameMoment::DEBUT:
        DrawTexture(backgroundTexture, 0, 0, LIGHTGRAY);
        DrawTexture(playButtonTexture, 500, 350, WHITE);
        break;
    case GameMoment::CREERREPRENDRE:
        DrawRectangle(0, 0, 650, 1000, RED);
        DrawRectangle(650, 0, 650, 1000, BLUE);
        DrawText("Charger une Partie", 20, 300, 50, BLACK);
        DrawText("Nouvelle Partie", 700, 300, 50, BLACK);
        break;
    default:
        break;
    }

    EndDrawing();
}
