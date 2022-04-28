#pragma once
#include "Unit.h"
#include "structures.h"

class Enemy : public Unit {

protected :
	int dep;
	int arr;
	virtual void Walk();
	void Kill();
public:
	Enemy(int x, int y, int dep, int arr);
	virtual int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	virtual void DrawUnit() override;
};