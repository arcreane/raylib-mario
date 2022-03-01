/*******************************************************************************************
*
*   raylib [core] example - 2d camera platformer
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Example contributed by arvyy (@arvyy) and reviewed by Ramon Santamaria (@raysan5)
*
*   Copyright (c) 2019 arvyy (@arvyy)
*
********************************************************************************************/


#include "Game.h"

int main(void)
{
    //pour pouvoir faire les tests,
    //SINON 
    //Game g1
    // world : 1 - current world : 1 - maxlevel ; 6 - unlocklevel : 5
    Game g1(1,1,6,3);
    g1.start();
    return 0;
}


