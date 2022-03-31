#pragma once
#include "Map.h"
#include "Player.h"
#include "LevelManager.h"

//define
#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

class Game
{
private:
	LevelManager* levelManager;

public:
	Game();
	~Game();

	void Start();
};

