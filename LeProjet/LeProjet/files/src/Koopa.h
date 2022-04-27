#pragma once
#include "Enemy.h"
#include "raylib.h"


class Koopa : public Enemy
{
private:
	Texture2D koopaText;
	Texture2D koopaText2;
public:
	Koopa(int x, int y, int dep, int arr);
	void Walk();
	void UpdateEnemy() override;
	void DrawEnemy() override;
	void Jump();
};


