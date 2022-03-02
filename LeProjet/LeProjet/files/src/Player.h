#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structures.h"

#define G 400

enum class Direction { right, left, up, down };

class Player
{
private:
	float playerJumpSpeed = 250.0f;
	float playerHorSpeed = 1000.0f;
public:
	Vector2 position;
	float speed;
	bool canJump;
	void attack();
	void UpdatePlayer(EnvItem* envItems, int envItemsLength, float delta);
};