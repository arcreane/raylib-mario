#pragma once
#include "Level.h"

class CharacterScreen : public Level
{
private:
    Texture2D validTexture;
    char name[25];
    int letterCount;
    Rectangle textBox;
    bool mouseOnText;
    Vector2 positionClick;
    int framesCounter;

public:
    CharacterScreen(LevelManager& levelManager);

    void InitLevel() override;
    void UpdateLevel() override;
    void DrawLevel() override;
};