#include "Goomba.h"

Goomba::Goomba(int x, int y, int dep, int arr)
    :Enemy(x, y, dep, arr)
{
    goombaText = LoadTexture("../LeProjet/LeProjet/files/img/goomba_retour.png");
    goombaText2 = LoadTexture("../LeProjet/LeProjet/files/img/goomba_alle.png");
    hitbox.height = 50;
    hitbox.width = 50;
}

void Goomba::Walk()
{
    if (position.x <= dep){
        direction = "goings";
    }
    if (position.x >= arr)
        direction = "comings";
    if (direction == "goings"){
        position.x += 0.1 * 10;
    }
    if (direction == "comings"){
        position.x -= 0.1 * 10;
    }    
}

void Goomba::UpdateEnemy()
{
    Walk();
}

void Goomba::DrawEnemy()
{
    if (direction == "goings")
        DrawTexture(goombaText2, position.x - 20, position.y - 32, LIGHTGRAY);
    if (direction == "comings")
        DrawTexture(goombaText, position.x - 20, position.y - 32, LIGHTGRAY);
}

