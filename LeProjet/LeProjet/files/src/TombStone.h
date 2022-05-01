#pragma once
#include "Enemy.h"

class TombStone : public Enemy
{
private:
	float SpeedFall;
public:
	TombStone(float x, float y, float dep, float arr);
	
	void DrawUnit() override;
	int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	
	void UpDown() override;
};

