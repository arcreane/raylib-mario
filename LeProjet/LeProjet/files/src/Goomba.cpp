#include "Goomba.h"
#include "raylib.h"

Goomba::Goomba(int x, int y, int dep, int arr)
    :Enemy(x, y, dep, arr)
{
    hUnitSpeed = 10;
    hitbox.height = 55;
    hitbox.width = 40;
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/goombaSprite.png");
    frameRec = { 2 * ((float)unitTexture.width / 5), 0.0f, (float)unitTexture.width / 5, (float)unitTexture.height };
}

void Goomba::DrawUnit()
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
