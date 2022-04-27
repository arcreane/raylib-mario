#pragma once
#include "raylib.h"
#include "structures.h"

#define G 600

enum class Direction { right, left, up, down, none };

class Unit
{
protected:
	float unitJumpSpeed = 350.0f;
	float hUnitSpeed = 400.0f;

	Rectangle hitbox;
	Direction hUnitDirection;
	Direction vUnitDirection;

	Texture2D unitTexture;

	// Animation
	Rectangle frameRec;
	int currentFrame;
	int framesCounter;
	int framesSpeed;

	void FlipSprite(bool hflip, bool vflip);
public:
	float speed;
	bool canJump;

	Vector2 position;


	Unit();
	virtual void InitUnit();
	virtual int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta);
	virtual void DrawUnit();
};

