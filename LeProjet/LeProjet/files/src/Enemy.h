#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

class Enemy : public Player {

public : 
	Rectangle hitbox;
	void Kill();
};