#include "Player.h"

void Player::attack()
{
}

void Player::UpdatePlayer(EnvItem* envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT))
    {
        if(this->position.x > 20)
        this->position.x -= playerHorSpeed * delta;
    }
    if (IsKeyDown(KEY_RIGHT)) this->position.x += playerHorSpeed * delta;
    if (IsKeyDown(KEY_SPACE) && this->canJump)
    {
        this->speed = -playerJumpSpeed;
        this->canJump = false;
    }
    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        Vector2* p = &(this->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + this->speed * delta)
        {
            hitObstacle = 1;
            this->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        this->position.y += this->speed * delta;
        this->speed += G * delta;
        this->canJump = false;
    }
    else this->canJump = true;
}
