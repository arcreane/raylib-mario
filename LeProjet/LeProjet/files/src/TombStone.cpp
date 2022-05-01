#include "TombStone.h"
#include "raylib.h"

TombStone::TombStone(int x, int y, int dep, int arr)
    : Enemy(x, y, dep, arr)
{
	hUnitSpeed = 0;
	vUnitSpeed = 10;
	SpeedFall = 30;
	hitbox.height = 95;
	hitbox.width = 95;
	hUnitDirection = Direction::none;
	unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/Tombstone100-100.png");
	frameRec = { 0.0f, 0.0f, (float)unitTexture.width, (float)unitTexture.height };
}

void TombStone::DrawUnit()
{
	DrawTextureRec(unitTexture, frameRec, Vector2({ position.x, position.y - unitTexture.height }), LIGHTGRAY);
}

int TombStone::UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta)
{
	UpDown();
    return 0;
}

void TombStone::UpDown()
{
	if (position.y >= dep) {
		vUnitDirection = Direction::up;
	}
	if (position.y <= arr)
		vUnitDirection = Direction::down;
	if (vUnitDirection == Direction::down) {
		position.y += 0.1 * SpeedFall;
	}
	if (vUnitDirection == Direction::up) {
		position.y -= 0.1 * vUnitSpeed;
	}
}
