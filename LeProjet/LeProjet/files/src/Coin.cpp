#include "Coin.h"

void Coin::UseItem(Level* l)
{
    l->score += 1;
    l->RemoveItem(this);
}

Coin::Coin() : Item(ItemType::coin) {}
