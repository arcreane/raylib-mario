#include "Game.h"
#include <cstring>
#include "structures.h"


//création de base
Game::Game()
{
	this->currentLevel = 1;
	this->world = 1;
	this->totalLevel = 6;
	this->unlockLevel = 1;

}

//pour faire nos test
Game::Game(int world, int currentLevel, int totalLevel, int unlockLevel)
{
	this->currentLevel = currentLevel;
	this->world = world;
	this->totalLevel = totalLevel;
	this->unlockLevel = unlockLevel;

}

void Game::start()
{
    typedef enum GameMoment { DEBUT, CHOISIRPARTIE, ENJEU };
    const int screenWidth = 1300;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Mario & DK Bros");

    //s'occupe du cube dans ENJEU
    Player player = { 0 };
    player.position = { 20 , 0 };
    player.speed = 0;
    player.canJump = false;

    //s'occupe du cube dans CHOISIRPARTIE
    Player playerMENU = { 0 };
    playerMENU.position = { 20 , 0 };
    playerMENU.speed = 0;
    playerMENU.canJump = false;


    //on devra stocker ça aussi

        //créer la MAPmonde1
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


    //fin des données à stocker


    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);
    

    int framesCounter = 0;
    int framesMax = 300 * 60;
    Camera2D camera = { 0 };
    Camera2D cameraMENU = { 0 };

    int cameraOption = 0;

    SetTargetFPS(60);
    GameMoment currentScreen = DEBUT;

     //Gestion de l'écran 1
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
            DrawTexture(button, (int)btnBounds.x, (int) btnBounds.y, WHITE); // Draw button frame
            if (btnAction)
            {
                currentScreen = CHOISIRPARTIE;
                cameraMENU.target = playerMENU.position;
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
            {{ -1000, -1000, 2000, 400 }, 0, LIGHTGRAY },
            {{ 0,0, 10000, 200 }, 1, DARKBROWN },
            {{ 0, 0, 40 , 40 }, 1, returnColorToPrint(1,&this->unlockLevel,&this->currentLevel)},
            {{ 300, 0, 40 , 40 }, 1, returnColorToPrint(2,&this->unlockLevel,&this->currentLevel)},
            {{ 600, 0, 40 , 40 }, 1, returnColorToPrint(3,&this->unlockLevel,&this->currentLevel)},
            {{ 900, 0, 40 , 40 }, 1, returnColorToPrint(4,&this->unlockLevel,&this->currentLevel)},
            {{ 1200, 0, 40 , 40 }, 1, returnColorToPrint(5,&this->unlockLevel,&this->currentLevel)},
            {{ 1500, 0, 40 , 40 }, 1, returnColorToPrint(6,&this->unlockLevel,&this->currentLevel)}
            };
            int envItemsLengthMAPmonde1 = sizeof(MAPmonde1) / sizeof(MAPmonde1[0]);
            float deltaTime = GetFrameTime();

            UpdateMAP(&playerMENU, MAPmonde1, envItemsLengthMAPmonde1, deltaTime, &this->currentLevel, &this->unlockLevel);
            cameraUpdaters[cameraOption](&cameraMENU, &playerMENU, MAPmonde1, envItemsLengthMAPmonde1, deltaTime, screenWidth, screenHeight);

            if (IsKeyPressed(KEY_B))
            {
                printf("Position de X: %f \nPosition de Y: %f \n ", playerMENU.position.x, playerMENU.position.y);
            }

            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(LIGHTGRAY);

            //Affichage des données sur l'écran ( chiant car *char )
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
            DrawTexture(youAreHere, playerMENU.position.x - 50, playerMENU.position.y - 105, LIGHTGRAY);
            EndMode2D();

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = ENJEU;
                camera.target = playerMENU.position;
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
            float deltaTime = GetFrameTime();
            UpdatePlayer(&player, envItems, envItemsLength, deltaTime);
            cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
            framesCounter++;

            if (IsKeyPressed(KEY_R))
            {
                camera.zoom = 1.0f;
                player.position = { 20, 0 };
            }
            if (player.position.y > 200)
            {
                DrawText("LOST", 100, 100, 100, DARKGRAY);
            }

            if (IsKeyPressed(KEY_B))
            {
                printf("Position de X: %f \nPosition de Y: %f \n ", player.position.x, player.position.y);
            }
            if (IsKeyPressed(KEY_N))
            {
                currentScreen = CHOISIRPARTIE;
                cameraMENU.target = playerMENU.position;
                cameraMENU.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
                cameraMENU.rotation = 0.0f;
                cameraMENU.zoom = 1.0f;
            }
            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            BeginMode2D(camera);
            for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);
            //Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };

            
            DrawTexture(mario, player.position.x -20, player.position.y -32, LIGHTGRAY); // Draw button frame
            EndMode2D();
           // DrawText("Controls:", 20, 20, 10, BLACK);
           DrawText("NOTE DEV: ", 40, 40, 10, DARKGRAY);
           DrawText("left - right - space | pour les déplacements", 40, 60, 10, DARKGRAY);
           DrawText("R : restart - B : affiche les coordonnees dans le terminal - N: retourne ecran 2", 40, 80, 10, DARKGRAY);

            std::string DispCurrentLevel = "Temps restant: " + std::to_string((framesMax/60) - (framesCounter/60));
            char const* Game3_time = DispCurrentLevel.c_str();  //use char const* as target type

            DrawText(Game3_time, 5, 0, 30, BLUE);
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

