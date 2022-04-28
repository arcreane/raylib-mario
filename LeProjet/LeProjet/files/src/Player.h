#pragma once
#include "Unit.h"
#include "structures.h"

class Player : public Unit
{
public:
	Player();
	void InitUnit() override;
	int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	void DrawUnit() override;
};