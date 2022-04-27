#include "Player.h"


Player::Player()
{
    position = { 0, 0 };
    speed = 0;
    canJump = false;
    playerHDirection = Direction::none;
    playerVDirection = Direction::none;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 9;
    playerTexture = LoadTexture("../LeProjet/LeProjet/files/img/marioSprites.png");
    frameRec = { 5 * ((float)playerTexture.width / 9), 0.0f, (float)playerTexture.width / 9, (float)playerTexture.height };
}

void Player::InitPlayer()
{
    speed = 0;
    canJump = false;
    playerHDirection = Direction::none;
    playerVDirection = Direction::none;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 9;
}

void Player::attack()
{
}

void Player::UpdatePlayer(EnvItem* envItems, int envItemsLength, float delta)
{   
    int hitTopSide = 0;
    int hitRightSide = 0;
    int hitLeftSide = 0;
    int hitBottomSide = 0;
    int hitAnySide = 0;
    if (playerVDirection != Direction::up)
    {
        playerHDirection = Direction::none;
    }
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
        if (IsKeyDown(KEY_LEFT)){
            if (ei->blocking[1] &&
                ei->rect.y < p->y &&
                ei->rect.y + ei->rect.height >= p->y &&
                ei->rect.x + ei->rect.width <= p->x &&
                ei->rect.x + ei->rect.width > p->x - this->playerHorSpeed * delta)
            {
                hitRightSide = 1;
                hitAnySide = 1;
                p->x = ei->rect.x + ei->rect.width;
            }
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
        if (IsKeyDown(KEY_RIGHT))
        {
            if (ei->blocking[3] &&
                ei->rect.y < p->y &&
                ei->rect.y + ei->rect.height >= p->y &&
                ei->rect.x >= p->x &&
                ei->rect.x < p->x + this->playerHorSpeed * delta)
            {
                hitLeftSide = 1;
                hitAnySide = 1;
                p->x = ei->rect.x;
            }
        }
        if (hitAnySide && ei->type== EnvItemType::finish)
        {
            //finishMap(); (in map.cpp)
        }
        
    }

    if (IsKeyDown(KEY_LEFT)) {
        playerHDirection = Direction::left;
        if (!hitRightSide)
        {
            if (this->position.x > 20)
                this->position.x -= playerHorSpeed * delta;
        }
    }
    if (IsKeyDown(KEY_RIGHT) && !hitLeftSide)
    {
        playerHDirection = Direction::right;
        if (!hitLeftSide)
        {
            this->position.x += playerHorSpeed * delta;
        }
    }
    if (IsKeyDown(KEY_SPACE) && this->canJump && !hitBottomSide)
    {
        playerVDirection = Direction::up;
        this->speed = -playerJumpSpeed;
        this->canJump = false;
    }
    if (!hitTopSide)
    {
        this->position.y += this->speed * delta;
        this->speed += G * delta;
        this->canJump = false;
    }
    else
    {
        playerVDirection = Direction::none;
        this->canJump = true;
    }
}

void Player::DrawPlayer() {
    if (playerVDirection == Direction::up) // Jumping
    {
        frameRec.x = (1 + (float)currentFrame) * (float)playerTexture.width / 9;
    }
    else // Not Jumping
    {
        if (playerHDirection != Direction::none) // Running
        {
            framesCounter++;
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 3) currentFrame = 0;

                frameRec.x = (5 + (float)currentFrame) * (float)playerTexture.width / 9;
            }
        }
        else // Idle
        {
            frameRec.x = 0;
        }
        
    }
    FlipSprite(playerHDirection != Direction::right, false);
    DrawTextureRec(playerTexture, frameRec, Vector2({ position.x - 25, position.y - 55 }), LIGHTGRAY);
}

void Player::FlipSprite(bool hflip, bool vflip) {
    frameRec.width = fabs(frameRec.width) * (hflip ? -1 : 1);
    frameRec.height = fabs(frameRec.height) * (vflip ? -1 : 1);
}