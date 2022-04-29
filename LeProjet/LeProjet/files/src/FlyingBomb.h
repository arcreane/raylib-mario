#pragma once
#include "Enemy.h"

class FlyingBomb : public Enemy
{
public:
	FlyingBomb(int x, int y, int dep, int arr);
	void DrawUnit() override;
	int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	void UpDown();
};

