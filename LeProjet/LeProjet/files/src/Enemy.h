#pragma once
#include "Unit.h"
#include "structures.h"
#include "Player.h"
#include "PlayableLevel.h"

class PlayableLevel;

class Enemy : public Unit
{
protected :
	float dep;
	float arr;
	virtual void Walk();
	virtual void UpDown();

public:
	Enemy(float x, float y, float dep, float arr);

	virtual int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	virtual void DrawUnit() override;

	void DetectPlayer(Player* p, PlayableLevel* l);
};