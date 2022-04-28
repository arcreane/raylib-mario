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
    //std::cout << vUnitSpeed << std::endl;
    /* if (vUnitSpeed > 0.0) is_falling = true;
    else is_falling = false; */
    if (p->GetPosition().x >= this->position.x &&
        p->GetPosition().x <= this->position.x + this->hitbox.width &&
        p->GetPosition().y >= this->position.y - this->hitbox.height &&
        p->GetPosition().y <= this->position.y)
    {
        hitOtherSide = 1;
    }
    else if (p->GetPosition().x >= this->position.x &&
        p->GetPosition().x <= this->position.x + this->hitbox.width &&
        p->GetPosition().y >= this->position.y - this->hitbox.height &&
        p->GetPosition().y <= this->position.y - this->hitbox.height + 5 &&
        hitOtherSide == 0)
    {
        this->Kill(l);
        // if (is_falling == true) this->kill;
    }
}
