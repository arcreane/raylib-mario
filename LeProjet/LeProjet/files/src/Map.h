#pragma once
#include "Player.h"

class Map
{
public:
	void UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel);
};

