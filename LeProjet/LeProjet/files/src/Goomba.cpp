#include "Goomba.h"
#include "raylib.h"

Goomba::Goomba(int x, int y, int dep, int arr)
    :Enemy(x, y, dep, arr)
{
    hUnitSpeed = 10;
    hitbox.height = 50;
    hitbox.width = 50;
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/goomba.png");
    frameRec = { 0.0f, 0.0f, (float)unitTexture.width, (float)unitTexture.height };
}
