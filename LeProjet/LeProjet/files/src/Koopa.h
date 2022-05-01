#pragma once
#include "Enemy.h"

class Koopa : public Enemy
{
public:
	Koopa(float x, float y, float dep, float arr);
	void DrawUnit() override;
};


