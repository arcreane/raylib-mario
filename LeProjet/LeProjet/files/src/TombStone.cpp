#include "TombStone.h"
#include "raylib.h"

TombStone::TombStone(int x, int y, int dep, int arr)
    : Enemy(x, y, dep, arr)
{
	hUnitSpeed = 5;
	SpeedFall = 20;
	hitbox.height = 85;
	hitbox.width = 63;
	unitTexture = LoadTexture("../LeProjet/LeProjet/files/img/Tombstone100-100.png");
	frameRec = { 2 * ((float)unitTexture.width / 5), 0.0f, (float)unitTexture.width / 5, (float)unitTexture.height };
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
		hUnitDirection = Direction::down;
	}
	if (position.y <= arr)
		hUnitDirection = Direction::up;
	if (hUnitDirection == Direction::up) {
		position.y += 0.1 * hUnitSpeed;
	}
	if (hUnitDirection == Direction::down) {
		position.y -= 0.1 * SpeedFall;
	}
}
