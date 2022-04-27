#pragma once
#include "Enemy.h"


class Koopa : public Enemy
{
public:
	Koopa(int x, int y, int dep, int arr);
private:
	void Jump();
};


