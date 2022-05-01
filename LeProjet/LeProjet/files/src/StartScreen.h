#pragma once
#include "Level.h"

enum class GameMoment { DEBUT, CREERREPRENDRE };

class StartScreen : public Level
{
private:
	GameMoment currentScreen;
	float frameHeight;
	Vector2 positionClick;

	Texture2D playButtonTexture;
	Texture2D backgroundTexture;

public:
	StartScreen(LevelManager& levelManager);

	virtual void InitLevel() override;
	virtual void UpdateLevel() override;
	virtual void DrawLevel() override;
};
