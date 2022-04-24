#include "Player.h"

void Player::attack()
{
}

void Player::UpdatePlayer(EnvItem* envItems, size_t envItemsLength, float delta)
{   
    int hitTopSide = 0;
    int hitRightSide = 0;
    int hitLeftSide = 0;
    int hitBottomSide = 0;
    int hitAnySide = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        Vector2* p = &(this->position);

        // Check if the player is in contact with the top side of a block
        if (ei->blocking[0] &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + this->speed * delta)
        {
            hitTopSide = 1;
            hitAnySide = 1;
            this->speed = 0.0f;
            p->y = ei->rect.y;
        }

        // Check if the player is in contact with the right side of a block
        if (IsKeyDown(KEY_LEFT) &&
            ei->blocking[1] &&
            ei->rect.y < p->y &&
            ei->rect.y + ei->rect.height >= p->y &&
            ei->rect.x + ei->rect.width <= p->x &&
            ei->rect.x + ei->rect.width > p->x - this->playerHorSpeed * delta)
        {
            hitRightSide = 1;
            hitAnySide = 1;
            p->x = ei->rect.x + ei->rect.width;
        }

        // Check if the player is in contact with the bottom side of a block
        if (ei->blocking[2] &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y + ei->rect.height <= p->y &&
            ei->rect.y + ei->rect.height > p->y + this->speed * delta)
        {
            hitBottomSide = 1;
            hitAnySide = 1;
            this->speed = 0.0f;
            p->y = ei->rect.y + ei->rect.height;
            
        }

        // Check if the player is in contact with the left side of a block
        if (IsKeyDown(KEY_RIGHT) &&
            ei->blocking[3] &&
            ei->rect.y < p->y &&
            ei->rect.y + ei->rect.height >= p->y &&
            ei->rect.x >= p->x &&
            ei->rect.x < p->x + this->playerHorSpeed * delta)
        {
            hitLeftSide = 1;
            hitAnySide = 1;
            p->x = ei->rect.x;
        }
        if (hitAnySide && ei->type== EnvItemType::finish)
        {
            //finishMap(); (in map.cpp)
        }
        
    }

    if (IsKeyDown(KEY_LEFT) && !hitRightSide)
    {
        if (this->position.x > 20)
            this->position.x -= playerHorSpeed * delta;
    }
    if (IsKeyDown(KEY_RIGHT) && !hitLeftSide) this->position.x += playerHorSpeed * delta;
    if (IsKeyDown(KEY_SPACE) && this->canJump && !hitBottomSide)
    {
        this->speed = -playerJumpSpeed;
        this->canJump = false;
    }
    if (!hitTopSide)
    {
        this->position.y += this->speed * delta;
        this->speed += G * delta;
        this->canJump = false;
    }
    else this->canJump = true;
}
