#pragma once
#include "Item.h"
#include "PlayableLevel.h"

class Coin : public Item
{
private:
	void UseItem(PlayableLevel* l) override;

public:
	Coin();
};

