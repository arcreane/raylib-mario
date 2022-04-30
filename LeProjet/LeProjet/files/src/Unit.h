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
	float vUnitSpeed;
	bool canJump;
	int lives;

	Vector2 position;
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
	Unit();

	virtual void InitUnit();
	virtual int UpdateUnit(EnvItem* envItems, size_t envItemsLength, float delta);
	virtual void DrawUnit();

	float GetVUnitSpeed();
	bool GetCanJump();
	int GetLives();
	Vector2 GetPosition();
	void SetLives(int lives);
	void SetPosition(Vector2 position);
};