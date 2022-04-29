#pragma once
#include "Item.h"

class UpMushroom : public Item
{
private:
	void UseItem(Player* p, PlayableLevel* l) override;

public:
	UpMushroom();
};

