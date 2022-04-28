#pragma once
#include "Unit.h"
#include "structures.h"
#include "Player.h"
#include "PlayableLevel.h"

class PlayableLevel;

class Enemy : public Unit
{
protected :
	int dep;
	int arr;
	virtual void Walk();

public:
	Enemy(int x, int y, int dep, int arr);

	virtual int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta) override;
	virtual void DrawUnit() override;

	void DetectPlayer(Player* p, PlayableLevel* l);
};