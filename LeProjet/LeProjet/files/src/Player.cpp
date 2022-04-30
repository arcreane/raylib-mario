#include "Player.h"


Player::Player()
    :Unit()
{
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/marioSprites.png");
    frameRec = { 5 * ((float)unitTexture.width / 9), 0.0f, (float)unitTexture.width / 9, (float)unitTexture.height };
}

void Player::InitUnit()
{
}

int Player::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{   
    int levelFinished = 0;
    int hitTopSide = 0;
    int hitRightSide = 0;
    int hitLeftSide = 0;
    int hitBottomSide = 0;
    int hitAnySide = 0;
    if (vUnitDirection != Direction::up)
    {
        hUnitDirection = Direction::none;
    }
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        Vector2* p = &(this->position);
        hitAnySide = 0;

        // Optimisation to check collision only if the player is near the environment item
        if (fabs(p->x - ei->rect.x) > 200
            && fabs(p->y - ei->rect.y) > 200)
        {
            continue;
        }

        // Check if the player is in contact with the top side of a block
        if (ei->blocking[0] &&
            ei->rect.x < p->x &&
            ei->rect.x + ei->rect.width > p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + this->vUnitSpeed * delta)
        {
            hitTopSide = 1;
            hitAnySide = 1;
            this->vUnitSpeed = 0.0f;
            p->y = ei->rect.y;
        }

        // Check if the player is in contact with the right side of a block
        if (IsKeyDown(KEY_LEFT)){
            if (ei->blocking[1] &&
                ei->rect.y < p->y &&
                ei->rect.y + ei->rect.height >= p->y &&
                ei->rect.x + ei->rect.width <= p->x &&
                ei->rect.x + ei->rect.width > p->x - this->hUnitSpeed * delta)
            {
                hitRightSide = 1;
                hitAnySide = 1;
                p->x = ei->rect.x + ei->rect.width;
            }
        }

        // Check if the player is in contact with the bottom side of a block
        if (ei->blocking[2] &&
            ei->rect.x < p->x &&
            ei->rect.x + ei->rect.width > p->x &&
            ei->rect.y + ei->rect.height <= p->y &&
            ei->rect.y + ei->rect.height > p->y + this->vUnitSpeed * delta)
        {
            hitBottomSide = 1;
            hitAnySide = 1;
            this->vUnitSpeed = 0.0f;
            p->y = ei->rect.y + ei->rect.height;
            
        }

        // Check if the player is in contact with the left side of a block
        if (IsKeyDown(KEY_RIGHT))
        {
            if (ei->blocking[3] &&
                ei->rect.y < p->y &&
                ei->rect.y + ei->rect.height >= p->y &&
                ei->rect.x >= p->x &&
                ei->rect.x < p->x + this->hUnitSpeed * delta)
            {
                hitLeftSide = 1;
                hitAnySide = 1;
                p->x = ei->rect.x;
            }
        }
        if (hitAnySide && ei->type== EnvItemType::finish)
        {
            levelFinished = 1;
        }
        
    }

    if (IsKeyDown(KEY_LEFT)) {
        hUnitDirection = Direction::left;
        if (!hitRightSide)
        {
            if (this->position.x > 20)
                this->position.x -= hUnitSpeed * delta;
        }
    }
    if (IsKeyDown(KEY_RIGHT) && !hitLeftSide)
    {
        hUnitDirection = Direction::right;
        if (!hitLeftSide)
        {
            this->position.x += hUnitSpeed * delta;
        }
    }
    if (IsKeyDown(KEY_SPACE) && this->canJump && !hitBottomSide)
    {
        vUnitDirection = Direction::up;
        this->vUnitSpeed = -unitJumpSpeed;
        this->canJump = false;
    }
    if (!hitTopSide)
    {
        this->position.y += this->vUnitSpeed * delta;
        this->vUnitSpeed += G * delta;
        this->canJump = false;
    }
    else
    {
        vUnitDirection = Direction::none;
        this->canJump = true;
    }
    return levelFinished;
}

void Player::DrawUnit() {
    if (vUnitDirection == Direction::up) // Jumping
    {
        frameRec.x = (1 + (float)currentFrame) * (float)unitTexture.width / 9;
    }
    else // Not Jumping
    {
        if (hUnitDirection != Direction::none) // Running
        {
            framesCounter++;
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 3) currentFrame = 0;

                frameRec.x = (5 + (float)currentFrame) * (float)unitTexture.width / 9;
            }
        }
        else // Idle
        {
            frameRec.x = 0;
        }
        
    }
    FlipSprite(hUnitDirection != Direction::right, false);
    DrawTextureRec(unitTexture, frameRec, Vector2({ position.x - 40, position.y - 55 }), LIGHTGRAY);
}