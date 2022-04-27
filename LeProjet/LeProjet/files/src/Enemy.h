#pragma once
#include "Player.h"
#include <string>

class Enemy : public Player {

protected :
	Rectangle hitbox;
	int dep;
	int arr;
	std::string direction;
public:
	Enemy(int x, int y, int dep, int arr);
	void Kill();
	virtual void UpdateEnemy();
	virtual void DrawEnemy();
};