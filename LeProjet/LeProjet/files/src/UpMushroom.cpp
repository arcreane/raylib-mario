#include "UpMushroom.h"

void UpMushroom::UseItem(Level* l)
{
	if (l->lives < 3) l->lives += 1;
	l->RemoveItem(this);
}

UpMushroom::UpMushroom() : Item(ItemType::upMushroom) {}