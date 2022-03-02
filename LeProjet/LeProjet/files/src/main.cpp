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

//include structures & fonctions




using namespace std;



#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main(void)
{
    //pour pouvoir faire les tests,
    //SINON 
    //Game g1
    // world : 1 - current world : 1 - maxlevel ; 6 - unlocklevel : 5
    Game g1(1,1,6,3);
    g1.start();
    return 0;
    
    //// Initialization
    ////--------------------------------------------------------------------------------------
    //const int screenWidth = 800;
    //const int screenHeight = 450;

    //InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    //// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    //Texture2D scarfy = LoadTexture("../LeProjet/LeProjet/files/img/scarfy.png");        // Texture loading

    //Vector2 position = { 350.0f, 280.0f };
    //Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height };
    //int currentFrame = 0;

    //int framesCounter = 0;
    //int framesSpeed = 8;            // Number of spritesheet frames shown by second

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    ////--------------------------------------------------------------------------------------

    //// Main game loop
    //while (!WindowShouldClose())    // Detect window close button or ESC key
    //{
    //    // Update
    //    //----------------------------------------------------------------------------------
    //    framesCounter++;

    //    if (framesCounter >= (60 / framesSpeed))
    //    {
    //        framesCounter = 0;
    //        currentFrame++;

    //        if (currentFrame > 5) currentFrame = 0;

    //        frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
    //    }

    //    if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
    //    else if (IsKeyPressed(KEY_LEFT)) framesSpeed--;

    //    if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
    //    else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;
    //    //----------------------------------------------------------------------------------

    //    // Draw
    //    //----------------------------------------------------------------------------------
    //    BeginDrawing();

    //    ClearBackground(RAYWHITE);

    //    DrawTextureRec(scarfy, frameRec, position, WHITE);  // Draw part of the texture

    //    EndDrawing();
    //    //----------------------------------------------------------------------------------
    //}

    //// De-Initialization
    ////--------------------------------------------------------------------------------------
    //UnloadTexture(scarfy);       // Texture unloading

    //CloseWindow();                // Close window and OpenGL context
    ////--------------------------------------------------------------------------------------

    //return 0;
}


