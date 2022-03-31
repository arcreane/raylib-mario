#pragma once
#include "Level.h"

class CharacterScreen : public Level
{
private:
	Texture2D validTexture;

public:
	CharacterScreen(LevelManager& levelManager);
	void InitLevel() override;
	void UpdateLevel() override;
	void DrawLevel() override;
};

