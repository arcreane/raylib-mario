#include "Game.h"
#include <cstring>
#include "structures.h"
#include "Menu.h"
#include "Player.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <fstream>


#define Enemy_Amount 1
using namespace std;

//cr�ation de base

Game::Game()
{
    this->currentLevel = 1;
    this->world = 1;
    this->totalLevel = 6;
    this->unlockLevel = 1;
    this->gameMap = new Map();

}

//pour faire nos test
Game::Game(int world, int currentLevel, int totalLevel, int unlockLevel)
{
    this->currentLevel = currentLevel;
    this->world = world;
    this->totalLevel = totalLevel;
    this->unlockLevel = unlockLevel;
    this->gameMap = new Map();

}

Game::~Game()
{
    delete gameMap;
}

void Game::start()
{
    // Store the map from a file
    gameMap->CreateMap("../LeProjet/LeProjet/files/map1.txt");

    typedef enum GameMoment { DEBUT, CHOISIRPARTIE, ENJEU };
    const int screenWidth = 1300;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Mario & DK Bros");

    //ENEMY à classer
    double previousTime = 0.0;
    double currentTime = GetTime();
    float deltaTime = 0.0f;
    double previousTime2 = 0.0;
    double currentTime2 = GetTime();
    float deltaTime2 = 0.0f;
    std::string direction = "goings";
    std::string direction2 = "goings";
    std::string tampon;

    // Create player
    Player* player = new Player();
    // Create player to choose the level in the menu
    Player* playerMENU = new Player();

    //s'occupe du cube dans ENJEU
    player->position = { 120 , -10 };
    player->speed = 0;
    player->canJump = false;

    //s'occupe du cube dans CHOISIRPARTIE
    playerMENU->position = { 20 , 0 };
    playerMENU->speed = 0;
    playerMENU->canJump = false;

    //ENEMY à classer
    static Enemy goomba[Enemy_Amount] = { 0 };

    static Enemy koopa[Enemy_Amount] = { 0 };

    for (int i = 0; i < Enemy_Amount; i++)
    {
        goomba[i].rec.width = 70;
        goomba[i].rec.height = 70;
        goomba[i].active = true;
        goomba[i].color = BLUE;
        goomba[i].position = { 80 , -15 };
    }

    for (int i = 0; i < Enemy_Amount; i++)
    {
        koopa[i].rec.width = 70;
        koopa[i].rec.height = 70;
        koopa[i].active = true;
        koopa[i].color = BLUE;
        koopa[i].position = { 100 , -15 };
    }



    Camera2D camera = { 0 };
    Camera2D cameraMENU = { 0 };

    int cameraOption = 0;

    SetTargetFPS(60);
    GameMoment currentScreen = DEBUT;

    //Gestion de l'�cran 1
    Texture2D button = LoadTexture("../LeProjet/LeProjet/files/img/play.png"); // Load button texture
    // Define frame rectangle for drawing
    float frameHeight = (float)button.height;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };
    // Define button bounds on screen
    Rectangle btnBounds = { screenWidth / 2.0f - button.width / 2.0f, screenHeight / 2.0f - button.height / 2.0f, (float)button.width, frameHeight };
    bool btnAction = false;         // Button action should be activated
    Vector2 mousePoint = { 0.0f, 0.0f };
    btnAction = false;

    Texture2D mario = LoadTexture("../LeProjet/LeProjet/files/img/mario.png"); // Load button texture
    Texture2D youAreHere = LoadTexture("../LeProjet/LeProjet/files/img/YouAreHere2.png"); // Load button texture
    Texture2D goombaText = LoadTexture("../LeProjet/LeProjet/files/img/goomba_retour.png");
    Texture2D goombaText2 = LoadTexture("../LeProjet/LeProjet/files/img/goomba_alle.png");
    Texture2D koopaText = LoadTexture("../LeProjet/LeProjet/files/img/koopa_alle.png");
    Texture2D koopaText2 = LoadTexture("../LeProjet/LeProjet/files/img/koopa_retour.png");

    Texture2D BlocTerre = LoadTexture("../LeProjet/LeProjet/files/img/BlocTerre100-100.png");
    Texture2D BlocInconnue = LoadTexture("../LeProjet/LeProjet/files/img/Ciel.png");

    int framesCounter = 0;
    int framesMax = 300 * 60;
    while (!WindowShouldClose())
    {
        //Goal : 3 Screen - mby 4 later about victory 

        switch (currentScreen)
        {
            //Page that ask user to press SPACE bar in ordre to go in screen 2
        case DEBUT:
        {


            mousePoint = GetMousePosition();


            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) btnAction = true;
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(button, (int)btnBounds.x, (int)btnBounds.y, WHITE); // Draw button frame
            if (btnAction)
            {
                currentScreen = CHOISIRPARTIE;
                cameraMENU.target = playerMENU->position;
                cameraMENU.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
                cameraMENU.rotation = 0.0f;
                cameraMENU.zoom = 1.0f;
            }
            EndDrawing();
        }
        break;
        //Page that ask user to cloose a LEVEL
        case CHOISIRPARTIE:
        {

            EnvItem MAPmonde1[] = {
            {{ -1000, -1000, 2000, 400 }, {0,0,0,0}, LIGHTGRAY, ItemType::sky},
            {{ 0,0, 10000, 200 }, {1,1,1,1}, DARKBROWN, ItemType::sky },
            {{ 0, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(1,&this->unlockLevel,&this->currentLevel),ItemType::sky},
            {{ 300, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(2,&this->unlockLevel,&this->currentLevel),ItemType::sky},
            {{ 600, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(3,&this->unlockLevel,&this->currentLevel),ItemType::sky},
            {{ 900, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(4,&this->unlockLevel,&this->currentLevel),ItemType::sky},
            {{ 1200, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(5,&this->unlockLevel,&this->currentLevel),ItemType::sky},
            {{ 1500, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(6,&this->unlockLevel,&this->currentLevel),ItemType::sky}
            };
            int envItemsLengthMAPmonde1 = sizeof(MAPmonde1) / sizeof(MAPmonde1[0]);
            float deltaTime = GetFrameTime();

            gameMap->UpdateMAP(playerMENU, MAPmonde1, envItemsLengthMAPmonde1, deltaTime, &this->currentLevel, &this->unlockLevel);
            cameraUpdaters[2](&cameraMENU, playerMENU, MAPmonde1, envItemsLengthMAPmonde1, deltaTime, screenWidth, screenHeight);

            if (IsKeyPressed(KEY_B))
            {
                printf("Position de X: %f \nPosition de Y: %f \n ", playerMENU->position.x, playerMENU->position.y);
            }

            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
 
            ClearBackground(LIGHTGRAY);

            //Affichage des donn�es sur l'�cran ( chiant car *char )
            std::string DispCurrentWorld = "Monde : " + std::to_string(this->world);
            char const* pchar = DispCurrentWorld.c_str();  //use char const* as target 
            std::string DispCurrentLevel = "Niveau : " + std::to_string(this->currentLevel);
            char const* pchar2 = DispCurrentLevel.c_str();  //use char const* as target type
            //printf("%d", g1.GetTotalLevel
            DrawText(pchar, 5, 0, 30, BLUE);
            DrawText(pchar2, 5, 40, 30, BLUE);

            BeginMode2D(cameraMENU);
            for (int i = 0; i < envItemsLengthMAPmonde1; i++) DrawRectangleRec(MAPmonde1[i].rect, MAPmonde1[i].color);
            //Rectangle playerRect = { playerMENU.position.x - 20, playerMENU.position.y - 40, 40, 40 };
            //DrawRectangleRec(playerRect, DARKBLUE);
            DrawTexture(youAreHere, playerMENU->position.x - 50, playerMENU->position.y - 105, LIGHTGRAY);


            for (size_t i = 0; i < this->totalLevel; i++)
            {
                std::string Dispniveauactuel = "Niveau: " + std::to_string(i+1);
                char const* NiveauActuel = Dispniveauactuel.c_str();  //use char const* as target type

                DrawText(NiveauActuel, -30 + i * 300, 50 , 40, BLUE);
            }
           


            EndMode2D();

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = ENJEU;
                camera.target = playerMENU->position;
                camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
                camera.rotation = 0.0f;
                camera.zoom = 1.0f;
            }
           
            EndDrawing();
        }
        break;
        //PLAY the choosen level
        case ENJEU:
        {
            framesCounter++;
            float deltaTime = GetFrameTime();
            player->UpdatePlayer(gameMap->mapVector.data(), gameMap->mapVector.size(), deltaTime);
            cameraUpdaters[cameraOption](&camera, player, gameMap->mapVector.data(), gameMap->mapVector.size(), deltaTime, screenWidth, screenHeight);

            if (IsKeyPressed(KEY_I))
            {
                cameraOption++;
                if (cameraOption == 6)
                    cameraOption = 0;
            }
            if (IsKeyPressed(KEY_R))
            {
                camera.zoom = 1.0f;
                player->position = { 20, 0 };
            }
            if (player->position.y > 200)
            {
                DrawText("LOST", 100, 100, 100, DARKGRAY);
            }

            if (IsKeyPressed(KEY_B))
            {
                printf("Position de X: %f \nPosition de Y: %f \n ", player->position.x, player->position.y);
            }
            if (IsKeyPressed(KEY_N))
            {
                currentScreen = CHOISIRPARTIE;
                cameraMENU.target = playerMENU->position;
                cameraMENU.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
                cameraMENU.rotation = 0.0f;
                cameraMENU.zoom = 1.0f;
            }
            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            BeginMode2D(camera);

            gameMap->DrawMap();

            //ENEMY à classer
            for (int i = 0; i < Enemy_Amount; i++)
            {
                if (goomba[i].active)
                {
                    currentTime = GetTime();
                    deltaTime = currentTime - previousTime;
                    if (goomba[i].position.x <= 70)
                        direction = "goings";
                    if (goomba[i].position.x >= 500)
                        direction = "comings";
                    if (direction == "goings")
                        goomba[i].position.x += 30 * deltaTime;
                    if (direction == "comings")
                        goomba[i].position.x -= 30 * deltaTime;
                    previousTime = currentTime;
                }
            }

            for (int i = 0; i < Enemy_Amount; i++)
            {
                if (koopa[i].active)
                {
                    currentTime2 = GetTime();
                    deltaTime2 = currentTime2 - previousTime2;
                    if (koopa[i].position.x <= 80)
                        direction2 = "goings";
                    if (koopa[i].position.x >= 400)
                        direction2 = "comings";
                    if (direction2 == "goings")
                        koopa[i].position.x += 40 * deltaTime2;
                    if (direction2 == "comings")
                        koopa[i].position.x -= 40 * deltaTime2;
                    previousTime2 = currentTime2;
                }
            }

            for (int i = 0; i < Enemy_Amount; i++)
            {
                if (goomba[i].active) {
                    if (direction == "goings")
                        DrawTexture(goombaText2, goomba[i].position.x - 20, goomba[i].position.y - 32, LIGHTGRAY);
                    if (direction == "comings")
                        DrawTexture(goombaText, goomba[i].position.x - 20, goomba[i].position.y - 32, LIGHTGRAY);
                }
            }

            for (int i = 0; i < Enemy_Amount; i++)
            {
                if (koopa[i].active) {
                    if (direction2 == "goings")
                        DrawTexture(koopaText, koopa[i].position.x - 20, koopa[i].position.y - 32, LIGHTGRAY);
                    if (direction2 == "comings")
                        DrawTexture(koopaText2, koopa[i].position.x - 20, koopa[i].position.y - 32, LIGHTGRAY);
                }
            }


            DrawTexture(mario, player->position.x - 20, player->position.y - 32, LIGHTGRAY); // Draw button frame
 
            EndMode2D();
            std::string DispCurrentLevel = "Temps restant: " + std::to_string((framesMax / 60) - (framesCounter / 60));
            char const* Game3_time = DispCurrentLevel.c_str();  //use char const* as target type

            DrawText(Game3_time, 5, 0, 30, RED);
            DrawText("Controls:", 20, 20, 10, BLACK);
            DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
            DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
            DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
            EndDrawing();


        }
        break;
        }


    }
    CloseWindow();        // Close window and OpenGL context

}











//--------------------
//
//--------------------
int Game::GetWorld()
{
    return world;
}

void Game::SetWorld(int c_world)
{
    this->world = c_world;
}

const int Game::GetCurrentLevel() const
{
    return currentLevel;
}

void Game::SetCurrentLevel(int c_level)
{
    this->currentLevel = c_level;
}

int Game::GetTotalLevel()
{
    return  totalLevel;
}

void Game::SetTotalLevel()
{
    this->totalLevel = 6;
}

int Game::GetUnlockLevel()
{
    return unlockLevel;
}

void Game::SetUnlockLevel(int c_unlocklevel)
{
    this->unlockLevel = c_unlocklevel;
}

void Game::UpdateMAPmonde1(Player* player, EnvItem* envItems, int envItemsLength, float delta, Game* g1)
{
    int framesCounter = 0;


    if (IsKeyPressed(KEY_LEFT))
    {
        if (g1->GetCurrentLevel() > 1)
        {

            player->position.x = player->position.x - 300;
            g1->SetCurrentLevel(g1->GetCurrentLevel() - 1);
            printf("%d \n", g1->GetCurrentLevel());
        }
        else printf("\n Tamer \n");
    }


    if (IsKeyPressed(KEY_RIGHT))
    {

        if (std::exp(g1->GetCurrentLevel()) < std::exp(g1->GetUnlockLevel()))
        {

            player->position.x = 20 + (g1->GetCurrentLevel() - 1) * 300 + 300;
            g1->SetCurrentLevel(g1->GetCurrentLevel() + 1);
            printf("%d \n", g1->GetCurrentLevel());
        }
    }
}
