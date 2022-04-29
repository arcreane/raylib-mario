#include "Goomba.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>



void Goomba::Walk(int dep, int arr)
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
   
    if (direction == "goings")
        DrawTexture(goombaText2, position.x - 20, position.y - 32, LIGHTGRAY);
    if (direction == "comings")
        DrawTexture(goombaText, position.x - 20, position.y - 32, LIGHTGRAY);
    
}

