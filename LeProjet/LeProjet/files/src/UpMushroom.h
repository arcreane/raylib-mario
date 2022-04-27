#pragma once
#include "Item.h"

class UpMushroom : public Item
{
private:
	void UseItem(PlayableLevel* l) override;
public:
	UpMushroom();
};

