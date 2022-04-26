#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "../../../../../MarioRay/LeProjet/LeProjet/files/src/Enemy.h"

class Koopa : public Enemy
{
public:
	Texture2D koopaText = LoadTexture("../LeProjet/LeProjet/files/img/koopa_alle.png");
	Texture2D koopaText2 = LoadTexture("../LeProjet/LeProjet/files/img/koopa_retour.png");
	Koopa(int x, int y) { hitbox.height = 70; hitbox.width = 70; position.x = x; position.y = y; }
	void Walk(int dep, int arr);
	void Jump();
};


