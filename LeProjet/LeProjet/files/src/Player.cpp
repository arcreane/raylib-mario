#include "Player.h"


void Player::move(Direction d)
{
}

void Player::jump()
{
}

void Player::attack()
{
}

void Player::UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT)) player->position.x -= playerHorSpeed * delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += playerHorSpeed * delta;
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -playerJumpSpeed;
        player->canJump = false;
    }
    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        Vector2* p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed * delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else player->canJump = true;
}