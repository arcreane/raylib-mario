#pragma once
#include "Enemy.h"
#include "raylib.h"

class Goomba : public Enemy
{
private:
	Texture2D goombaText;
	Texture2D goombaText2;
public:
	Goomba(int x, int y, int dep, int arr);
	void Walk();
	void UpdateEnemy() override;
	void DrawEnemy() override;
};


