#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(float x, float y, float dep, float arr);
	void DrawUnit() override;
};


