#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"


class Goomba : public Enemy
{
public:
	std::string direction = "goings";
	Texture2D goombaText = LoadTexture("../LeProjet/LeProjet/files/img/goomba_retour.png");
	Texture2D goombaText2 = LoadTexture("../LeProjet/LeProjet/files/img/goomba_alle.png");
	Goomba(int x, int y) { hitbox.height = 50; hitbox.width = 50; position.x = x; position.y = y; }
	void Walk(int dep, int arr);
};


