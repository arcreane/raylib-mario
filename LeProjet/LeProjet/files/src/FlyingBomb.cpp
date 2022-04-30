#include "FlyingBomb.h"
#include "raylib.h"

FlyingBomb::FlyingBomb(int x, int y, int dep, int arr)
	: Enemy(x, y, dep, arr)
{
	hUnitSpeed = 5;
	hitbox.height = 85;
	hitbox.width = 63;
	unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/bombSprite.png");
	frameRec = { 2 * ((float)unitTexture.width / 5), 0.0f, (float)unitTexture.width / 5, (float)unitTexture.height };
}

void FlyingBomb::DrawUnit()
{
	framesCounter++;
	if (framesCounter >= (60 / framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 4) currentFrame = 0;

		frameRec.x = (2 + (float)currentFrame) * (float)unitTexture.width / 5;
	}
	DrawTextureRec(unitTexture, frameRec, Vector2({ position.x, position.y - unitTexture.height}), LIGHTGRAY);
}

int FlyingBomb::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{
	UpDown();
	return 0;
}

void FlyingBomb::UpDown()
{
	if (position.y >= dep) {
		hUnitDirection = Direction::down;
	}
	if (position.y <= arr)
		hUnitDirection = Direction::up;
	if (hUnitDirection == Direction::up) {
		position.y += 0.1 * hUnitSpeed;
	}
	if (hUnitDirection == Direction::down) {
		position.y -= 0.1 * hUnitSpeed;
	}
}


