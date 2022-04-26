#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structures.h"

#define G 400

enum class Direction { right, left, up, down };
//class Level;

class Player
{
private:
	float playerJumpSpeed = 350.0f;
	float playerHorSpeed = 400.0f;
public:
	Vector2 position;
	float speed;
	bool canJump = false;
	int UpdatePlayer(EnvItem* envItems, size_t envItemsLength, float delta);
};