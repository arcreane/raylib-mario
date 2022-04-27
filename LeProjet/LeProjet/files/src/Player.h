#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structures.h"

#define G 600

enum class Direction { right, left, up, down, none };

class Player
{
private:
	float playerJumpSpeed = 350.0f;
	float playerHorSpeed = 400.0f;
	Direction playerHDirection;
	Direction playerVDirection;
	Rectangle frameRec;
	int currentFrame;
	int framesCounter;
	int framesSpeed;

	Texture2D playerTexture;
	void FlipSprite(bool hflip, bool vflip);

public:
	Vector2 position;
	float speed;
	bool canJump;

	Player();
	void InitPlayer();
	int UpdatePlayer(EnvItem* envItems, size_t envItemsLength, float delta);
	void DrawPlayer();
};