#pragma once
#include "Enemy.h"

class TombStone : public Enemy
{
public:
	float SpeedFall;
	TombStone(int x, int y, int dep, int arr);
	
	void DrawUnit() override;
	int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	
	void UpDown() override;
};

