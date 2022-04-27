#include "UpMushroom.h"

void UpMushroom::UseItem(PlayableLevel* l)
{
	int lives = l->GetLives();
	if (lives < 3) l->SetLives(lives + 1);
	l->RemoveItem(this);
}

UpMushroom::UpMushroom() : Item(ItemType::upMushroom)
{
	itemTexture = LoadTexture("../LeProjet/LeProjet/files/img/upMushroom50-50.png");
}