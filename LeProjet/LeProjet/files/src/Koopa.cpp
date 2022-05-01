#include "Koopa.h"
#include "raylib.h"

Koopa::Koopa(float x, float y, float dep, float arr)
    : Enemy(x,y,dep,arr)
{
    hUnitSpeed = 20;
    hitbox.height = 50;
    hitbox.width = 45;
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
