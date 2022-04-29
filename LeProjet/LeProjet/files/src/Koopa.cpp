#include "Koopa.h"
#include "raylib.h"

Koopa::Koopa(int x, int y, int dep, int arr)
    : Enemy(x,y,dep,arr)
{
    hUnitSpeed = 20;
    hitbox.height = 70;
    hitbox.width = 70;
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/koopa.png");
    frameRec = { 0.0f, 0.0f, (float)unitTexture.width, (float)unitTexture.height };
}
