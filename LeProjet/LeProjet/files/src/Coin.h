#pragma once
#include "Item.h"

class Coin : public Item
{
private:
	void UseItem(Level *l) override;
public:
	Coin();
};

