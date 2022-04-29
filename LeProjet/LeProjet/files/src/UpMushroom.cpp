#include "UpMushroom.h"

void UpMushroom::UseItem(Player *p, PlayableLevel* l)
{
	int lives = p->GetLives();
	if (lives < 3) p->SetLives(lives + 1);
	l->RemoveItem(this);
}

UpMushroom::UpMushroom() : Item(ItemType::upMushroom)
{
	itemTexture = LoadTexture("../LeProjet/LeProjet/files/img/upMushroom50-50.png");
}