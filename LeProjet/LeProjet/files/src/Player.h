#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structures.h"

#define G 400

enum class Direction { right, left, up, down };

class Player
{
public:
	int range;
	int dmg;
	float playerJumpSpeed = 250.0f;
	float playerHorSpeed = 2000.0f;
	Vector2 position;
	float speed;
	bool canJump;
	void move(Direction d);
	void jump();
	void attack();
	void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);
};