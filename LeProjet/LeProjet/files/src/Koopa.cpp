#include "Koopa.h"
#include "raylib.h"

Koopa::Koopa(int x, int y, int dep, int arr)
    : Enemy(x,y,dep,arr)
{
    hUnitSpeed = 20;
    hitbox.height = 70;
    hitbox.width = 70;
    //unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/koopa.png");
    //frameRec = { 0.0f, 0.0f, (float)unitTexture.width, (float)unitTexture.height };
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/koopaSprite.png");
    frameRec = { 2 * ((float)unitTexture.width / 5), 0.0f, (float)unitTexture.width / 5, (float)unitTexture.height };
}

void Koopa::DrawUnit()
{
    if (vUnitDirection != Direction::up)
    {
        if (hUnitDirection != Direction::none) // Running
        {
            framesCounter++;
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 4) currentFrame = 0;

                frameRec.x = (2 + (float)currentFrame) * (float)unitTexture.width / 5;
            }
        }
    }

    FlipSprite(hUnitDirection != Direction::right, false);
    DrawTextureRec(unitTexture, frameRec, Vector2({ position.x, position.y - unitTexture.height }), LIGHTGRAY);
}
