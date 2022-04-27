#include "Unit.h"

Unit::Unit()
{
    position = { 0, 0 };
    speed = 0;
    canJump = false;
    hitbox = { 0,0,0,0 };
    hUnitDirection = Direction::none;
    vUnitDirection = Direction::none;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 9;
    unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/marioSprites.png");
    frameRec = { 5 * ((float)unitTexture.width / 9), 0.0f, (float)unitTexture.width / 9, (float)unitTexture.height };
}

void Unit::InitUnit()
{
    speed = 0;
    canJump = false;
    hUnitDirection = Direction::none;
    vUnitDirection = Direction::none;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 9;
}

int Unit::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{
    return 0;
}

void Unit::DrawUnit()
{
}

void Unit::FlipSprite(bool hflip, bool vflip) {
    frameRec.width = fabs(frameRec.width) * (hflip ? -1 : 1);
    frameRec.height = fabs(frameRec.height) * (vflip ? -1 : 1);
}
