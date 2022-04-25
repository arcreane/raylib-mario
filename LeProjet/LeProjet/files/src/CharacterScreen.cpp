#include "CharacterScreen.h"

CharacterScreen::CharacterScreen(LevelManager& levelManager)
    :Level(LevelName::characterScreen, LevelName::menu, levelManager)
{
    validTexture = LoadTexture("../LeProjet/LeProjet/files/img/valider.png");
}

void CharacterScreen::InitLevel()
{
}

void CharacterScreen::UpdateLevel()
{
}

void CharacterScreen::DrawLevel()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Nom du joueur :", 100, 100, 40, BLACK);
    DrawRectangle(400, 400, 50, 50, RED);
    DrawRectangle(700, 400, 50, 50, RED);
    DrawText("Mario", 380, 300, 40, BLACK);
    DrawText("DK", 700, 300, 40, BLACK);
    DrawTexture(validTexture, 550, 550, WHITE); // Draw button frame

    EndDrawing();
}


