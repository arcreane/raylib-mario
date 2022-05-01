#pragma once
#include "Map.h"
#include "Player.h"
#include "LevelManager.h"

class Game
{
private:
	LevelManager* levelManager;

public:
	Game();
	~Game();

	void Start();
};

