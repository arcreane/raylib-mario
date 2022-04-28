#include "Enemy.h"

Enemy::Enemy(int x, int y, int dep, int arr)
	:Unit()
{
	this->dep = dep;
	this->arr = arr,
	this->position.x = x;
	this->position.y = y;
	this->hUnitDirection = Direction::right;
}

void Enemy::Kill(PlayableLevel* l)
{
    l->RemoveEnemy(this);
}

int Enemy::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{
    Walk();
    return 0;
}

void Enemy::DrawUnit()
{
	FlipSprite(hUnitDirection != Direction::right, false);
    DrawTextureRec(unitTexture, frameRec, Vector2({ position.x - 20, position.y - 32 }), LIGHTGRAY);
}

void Enemy::Walk()
{
    if (position.x <= dep) {
        hUnitDirection = Direction::right;
    }
    if (position.x >= arr)
        hUnitDirection = Direction::left;
    if (hUnitDirection == Direction::right) {
        position.x += 0.1 * hUnitSpeed;
    }
    if (hUnitDirection == Direction::left) {
        position.x -= 0.1 * hUnitSpeed;
    }
}

void Enemy::DetectPlayer(Player* p, PlayableLevel* l)
{
    int hitTopSide = 0;
    int hitOtherTopSide = 0;
    if (p->GetPosition().x >= this->position.x && //gauhe
        p->GetPosition().x <= this->position.x + this->hitbox.width && //droite
        p->GetPosition().y >= this->position.y && //bas
        p->GetPosition().y <= this->position.y + this->hitbox.height //haut
        )
    {
        this->Kill(l);
    }
    /*if (p->GetPosition().y == this->position.y &&
        p->GetPosition().x >= this->position.x && 
        p->GetPosition().x <= this->position.x + this->hitbox.width)
    {
        this->Kill(l);
    }*/
}
