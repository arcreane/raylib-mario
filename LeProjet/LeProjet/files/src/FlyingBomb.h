#pragma once
#include "Enemy.h"

class FlyingBomb : public Enemy
{
public:
	FlyingBomb(float x, float y, float dep, float arr);

	void DrawUnit() override;
	int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
};

