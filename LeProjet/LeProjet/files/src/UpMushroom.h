#pragma once
#include "Item.h"

class UpMushroom : public Item
{
private:
	void UseItem(Level* l) override;
public:
	UpMushroom();
};

