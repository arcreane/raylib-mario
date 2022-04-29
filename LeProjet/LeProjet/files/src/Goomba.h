#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(int x, int y, int dep, int arr);
	void DrawUnit() override;
};


