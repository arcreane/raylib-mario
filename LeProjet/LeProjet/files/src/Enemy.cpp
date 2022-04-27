#include "Enemy.h"

Enemy::Enemy(int x, int y, int dep, int arr)
{
	this->dep = dep;
	this->arr = arr,
	position.x = x;
	position.y = y;
	direction = "goings";
	hitbox = {0,0,0,0};
}

void Enemy::Kill()
{
}

void Enemy::UpdateEnemy()
{
}

void Enemy::DrawEnemy()
{
}
