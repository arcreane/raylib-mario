#include "Coin.h"

void Coin::UseItem(Player* p, PlayableLevel* l)
{
    l->SetScore(l->GetScore()+1);
    l->RemoveItem(this);
}

Coin::Coin() : Item(ItemType::coin)
{
    itemTexture = LoadTexture("../LeProjet/LeProjet/files/img/Coin50-50.png");
}
