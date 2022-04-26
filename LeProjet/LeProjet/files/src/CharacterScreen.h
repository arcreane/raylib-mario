#pragma once
#include "Level.h"

class CharacterScreen : public Level
{
private:
    Texture2D validTexture;
    char name[25];      // NOTE: One extra space required for null terminator char '\0'
    int letterCount;
    Rectangle textBox;
    bool mouseOnText;
    Vector2 positionClick;
public:
    CharacterScreen(LevelManager& levelManager);
    void InitLevel() override;
    void UpdateLevel() override;
    void DrawLevel() override;
};