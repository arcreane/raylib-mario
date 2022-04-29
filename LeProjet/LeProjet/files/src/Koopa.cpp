#include "Koopa.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>



void Koopa::Walk(int dep, int arr)
{
    double previousTime = 0.0;
    double currentTime = GetTime();
    float deltaTime = 0.0f;

    

    currentTime = GetTime();
    deltaTime = currentTime - previousTime;

    if (position.x <= dep) {
        direction2 = "goings";
    }
    if (position.x >= arr)
        direction2 = "comings";
    if (direction2 == "goings") {
        position.x += 0.1 * 20;
    }
    if (direction2 == "comings") {
        position.x -= 0.1 * 20;
    }
    previousTime = currentTime;


    if (direction2 == "goings")
        DrawTexture(koopaText, position.x - 20, position.y - 32, LIGHTGRAY);
    if (direction2 == "comings")
        DrawTexture(koopaText2, position.x - 20, position.y - 32, LIGHTGRAY);

}


void Koopa::Jump()
{
}

