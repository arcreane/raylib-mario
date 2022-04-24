#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structures.h"

#define G 400

enum class Direction { right, left, up, down };

class Player
{
private:
	float playerJumpSpeed = 350.0f;
	float playerHorSpeed = 400.0f;
public:
	Vector2 position;
	float speed;
	bool canJump = false;
	void attack();
	void UpdatePlayer(EnvItem* envItems, size_t envItemsLength, float delta);
};