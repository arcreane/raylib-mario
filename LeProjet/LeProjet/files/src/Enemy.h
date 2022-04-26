#pragma once
#include "raylib.h"
#include "raymath.h"

class Enemy {

public : 
	Rectangle hitbox;
	Vector2 position;

	void Kill();
};