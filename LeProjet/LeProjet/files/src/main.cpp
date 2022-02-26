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

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

#define G 400
#define PLAYER_JUMP_SPD 250.0f
#define PLAYER_HOR_SPD 2000.0f

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;


void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta);

void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraEvenOutOnLanding(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Mario & DK Bros");

    Player player = { 0 };
    player.position = { 20   , -100};
    player.speed = 0;
    player.canJump = false;

    //créer la map
    EnvItem envItems[] = {
        // 1 :X    -- 2:Y    --- 3:Distance    --- 4 : Hauteur
        // 1 : => + -- vers le bas +
        {{ -1000, -1000, 2000, 0 }, 0, LIGHTGRAY },
        {{ 0, 0, 10000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    EnvItem envItems2[] = {
    {{ -1000, -1000, 2000, 400 }, 0, LIGHTGRAY },
    {{ 0, 400, 10000, 200 }, 1, BLUE },
    {{ 300, 200, 400, 10 }, 1, BLUE},
    {{ 250, 300, 100, 10 }, 1, BLUE},
    {{ 650, 300, 100, 10 }, 1, BLUE}
    };

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Store pointers to the multiple update camera functions
    void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
        UpdateCameraCenter,
        UpdateCameraCenterInsideMap,
        UpdateCameraCenterSmoothFollow,
        UpdateCameraEvenOutOnLanding,
        UpdateCameraPlayerBoundsPush
    };

    int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters) / sizeof(cameraUpdaters[0]);

    int noPartie = 1;
    char a;
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    //informations à set avant tout:
    bool Etape1nomDuJouer = false;
    //Page 1 : demander au joueur de cliquer sur jouer
    //quand il clique, ça set le Etape

    //--------------------
    //Il faut ensuite set le monde dans lequel il joue
    int Etape2WorldNo;

    //------

    //puis la partie sur laquelle il à positionné son personnage
    int Etape3NoPartie;






    // Main game loop
    while (!WindowShouldClose())
    {
     /* while (!Etape1nomDuJouer) {
          float deltaTime = GetFrameTime();
          BeginDrawing();
          DrawText("LOST", 100, 100, 100, DARKGRAY);
          EndDrawing();
          if (IsKeyPressed(KEY_R))
          {
              Etape1nomDuJouer = !Etape1nomDuJouer;
          }
      }*/
        if (noPartie==1){

            float deltaTime = GetFrameTime();
            UpdatePlayer(&player, envItems, envItemsLength, deltaTime);
            cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);

            if (IsKeyPressed(KEY_R))
            {
                camera.zoom = 1.0f;
                player.position =  { 20, 0 };
               // if (noPartie == 1) noPartie = 2;
               // else if (noPartie == 2) noPartie = 1;
            }
            if (player.position.y>200)
            {
                DrawText("LOST", 100, 100, 100, DARKGRAY);
            }

            if (IsKeyPressed(KEY_B))
            {
                printf("Position de X: %f \nPosition de Y: %f \n ", player.position.x, player.position.y);
            }
            
            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            BeginMode2D(camera);
            for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);
            Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };
            DrawRectangleRec(playerRect, RED);
            EndMode2D();
            DrawText("Controls:", 20, 20, 10, BLACK);
            DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
            DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
            DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
            EndDrawing();
        }
       
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}

void UpdatePlayer(Player* player, EnvItem* envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT))
    {
        player->position.x -= PLAYER_HOR_SPD * delta;
    }
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        Vector2* p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed * delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed * delta;
        player->speed += G * delta;
        player->canJump = false;
    }
    else player->canJump = true;
}

void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset =  { width / 2.0f, height / 2.0f };
    camera->target = player->position;
}

void UpdateCameraCenterInsideMap(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset =  { width / 2.0f, height / 2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D(  { maxX, maxY }, * camera);
    Vector2 min = GetWorldToScreen2D(  { minX, minY }, * camera);

    if (max.x < width) camera->offset.x = width - (max.x - width / 2);
    if (max.y < height) camera->offset.y = height - (max.y - height / 2);
    if (min.x > 0) camera->offset.x = width / 2 - min.x;
    if (min.y > 0) camera->offset.y = height / 2 - min.y;
}

void UpdateCameraCenterSmoothFollow(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset =  { width / 2.0f, height / 2.0f };
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length));
    }
}

void UpdateCameraEvenOutOnLanding(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset =  { width / 2.0f, height / 2.0f };
    camera->target.x = player->position.x;

    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed * delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera->target.y -= evenOutSpeed * delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->position.y;
        }
    }
}

void UpdateCameraPlayerBoundsPush(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D(  { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height }, * camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D(  { (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height }, * camera);
    camera->offset =  { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}



//réglage de caméra
/*            if (camera.zoom > 3.0f) camera.zoom = 3.0f;
            else if (camera.zoom < 0.25f) camera.zoom = 0.25f;
            camera.zoom += ((float)GetMouseWheelMove() * 0.05f);*/

//caméra placement
/* if (IsKeyPressed(KEY_C)) cameraOption = (cameraOption + 1) % cameraUpdatersLength;
            // Call update camera function by its pointer
            cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);*/














/*******************************************************************************************
*
*   raylib [text] example - Input Box
*
*   This example has been created using raylib 3.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2017 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
/*
#include "raylib.h"

#define MAX_INPUT_CHARS     9

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "écriture vide");



    SetTargetFPS(10);               // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tapez sur espace pour quitter cette fenetre", 240, 140, 20, GRAY);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
*/
