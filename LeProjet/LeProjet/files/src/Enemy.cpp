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

int Enemy::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{
    Walk();
    return 0;
}

void Enemy::DrawUnit()
{
	FlipSprite(hUnitDirection != Direction::right, false);
    DrawTextureRec(unitTexture, frameRec, Vector2({ position.x, position.y - unitTexture.height}), LIGHTGRAY);
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
    int hitOtherSide = 0;
    bool is_falling;
    if (p->GetPosition().x >= this->position.x &&
        p->GetPosition().x <= this->position.x + this->hitbox.width &&
        p->GetPosition().y >= this->position.y - this->hitbox.height &&
        p->GetPosition().y <= this->position.y - this->hitbox.height + 7)
    {
        l->RemoveEnemy(this);
        hitTopSide = 1;
    }
    if (p->GetPosition().x >= this->position.x &&
        p->GetPosition().x <= this->position.x + this->hitbox.width &&
        p->GetPosition().y >= this->position.y - this->hitbox.height &&
        p->GetPosition().y <= this->position.y &&
        hitTopSide != 1)
    {
        l->RespawnPlayer();
        p->SetLives(p->GetLives()-1);
    }
}
