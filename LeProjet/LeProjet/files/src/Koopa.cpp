#include "Koopa.h"

Koopa::Koopa(int x, int y, int dep, int arr)
    : Enemy(x,y,dep,arr)
{
    koopaText = LoadTexture("../LeProjet/LeProjet/files/img/koopa_alle.png");
    koopaText2 = LoadTexture("../LeProjet/LeProjet/files/img/koopa_retour.png");
    hitbox.height = 70;
    hitbox.width = 70;
}

void Koopa::Walk()
{
    if (position.x <= dep) {
        direction = "goings";
    }
    if (position.x >= arr)
        direction = "comings";
    if (direction == "goings") {
        position.x += 0.1 * 20;
    }
    if (direction == "comings") {
        position.x -= 0.1 * 20;
    }
}

void Koopa::UpdateEnemy()
{
    Walk();
}

void Koopa::DrawEnemy()
{
    if (direction == "goings")
        DrawTexture(koopaText, position.x - 20, position.y - 32, LIGHTGRAY);
    if (direction == "comings")
        DrawTexture(koopaText2, position.x - 20, position.y - 32, LIGHTGRAY);
}


void Koopa::Jump()
{
}

