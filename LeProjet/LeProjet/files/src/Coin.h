#pragma once
#include "Item.h"

class Coin : public Item
{
protected:
	void UseItem(Level *l) override;
public:
	Coin();
};

