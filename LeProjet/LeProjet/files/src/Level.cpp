#include "Level.h"
#include "camera.h"
#include <iostream>
#include <fstream>


Level::Level(LevelName name, LevelManager& levelManager)
{
	this->name = name;
	this->levelManager = &levelManager;

	camera = { 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	cameraOption = 0;

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

    //ENEMY � classer
    enemyAmount = 1;
    previousTime = 0.0;
    currentTime = GetTime();
    deltaTime = 0.0f;
    previousTime2 = 0.0;
    currentTime2 = GetTime();
    deltaTime2 = 0.0f;
    direction = "goings";
    direction2 = "goings";

    marioTexture = LoadTexture("../LeProjet/LeProjet/files/img/mario.png");
    goombaTexture = LoadTexture("../LeProjet/LeProjet/files/img/goomba_retour.png");
    goombaTexture2 = LoadTexture("../LeProjet/LeProjet/files/img/goomba_alle.png");
    koopaTexture = LoadTexture("../LeProjet/LeProjet/files/img/koopa_alle.png");
    koopaTexture2 = LoadTexture("../LeProjet/LeProjet/files/img/koopa_retour.png");
    
    // Item Texture 
    CoinTexture = LoadTexture("../LeProjet/LeProjet/files/img/Coin100-100.png");
    ShroomTexture = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
}

void Level::InitLevel()
{
	switch (name)
	{
	case LevelName::lvl1:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
		camera.target = player.position;
		camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		camera.rotation = 0.0f;
		camera.zoom = 1.0f;

        player.position = { 120 , -10 };
        player.speed = 0;
        player.canJump = false;

        framesCounter = 0;
        framesMax = 300 * 60;

        //ENEMY � classer
        for (int i = 0; i < enemyAmount; i++)
        {
            Enemy goombaEnemy;
            goombaEnemy.rec.width = 70;
            goombaEnemy.rec.height = 70;
            goombaEnemy.active = true;
            goombaEnemy.color = BLUE;
            goombaEnemy.position = { 80 , -15 };
            goomba.push_back(goombaEnemy);
        }
        for (int i = 0; i < enemyAmount; i++)
        {
            Enemy koopaEnemy;
            koopaEnemy.rec.width = 70;
            koopaEnemy.rec.height = 70;
            koopaEnemy.active = true;
            koopaEnemy.color = BLUE;
            koopaEnemy.position = { 100 , -15 };
            koopa.push_back(koopaEnemy);
        }
		break;
	case LevelName::lvl2:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl3:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl4:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl5:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl6:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
		break;
	default:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
	}
}

void Level::UpdateLevel()
{
    framesCounter++;
    float deltaTime = GetFrameTime();
    player.UpdatePlayer(map.mapVector.data(), map.mapVector.size(), deltaTime);
    cameraUpdaters[cameraOption](&camera, &player, map.mapVector.data(), map.mapVector.size(), deltaTime, screenWidth, screenHeight);

    if (IsKeyPressed(KEY_I))
    {
        cameraOption++;
        if (cameraOption == 6)
            cameraOption = 0;
    }
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
        levelManager->LoadLevel(LevelName::menu);
    }
}

void Level::DrawLevel()
{
    BeginDrawing();

    BeginMode2D(camera);

    map.DrawMap();
    this->DrawItem();

    //ENEMY � classer
    for (int i = 0; i < enemyAmount; i++)
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

    for (int i = 0; i < enemyAmount; i++)
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

    for (int i = 0; i < enemyAmount; i++)
    {
        if (goomba[i].active) {
            if (direction == "goings")
                DrawTexture(goombaTexture2, goomba[i].position.x - 20, goomba[i].position.y - 32, LIGHTGRAY);
            if (direction == "comings")
                DrawTexture(goombaTexture, goomba[i].position.x - 20, goomba[i].position.y - 32, LIGHTGRAY);
        }
    }

    for (int i = 0; i < enemyAmount; i++)
    {
        if (koopa[i].active) {
            if (direction2 == "goings")
                DrawTexture(koopaTexture, koopa[i].position.x - 20, koopa[i].position.y - 32, LIGHTGRAY);
            if (direction2 == "comings")
                DrawTexture(koopaTexture2, koopa[i].position.x - 20, koopa[i].position.y - 32, LIGHTGRAY);
        }
    }


    DrawTexture(marioTexture, player.position.x - 20, player.position.y - 32, LIGHTGRAY); // Draw button frame

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

void Level::ReadItems(std::string filename)
{
    char c;   // To read each character from file
    std::vector<char> charVector;
    float line = 0;    // Variable to keep count of each line
    float col = 0;    // Variable to keep count of each colone
    std::ifstream mFile(filename);
    if (mFile.is_open())
    {
        while (!mFile.eof())
        {
            mFile.get(c);  // read character
            if (c == '\n')
            {
                line++;
                col = 0;
            }
            else if (c != 'z')
            {
                Item item = CreateItem(c, line, col);
                itemVector.push_back(item);
            }
            col++;
        }
        mFile.close();
    }
    else
        std::cout << "Couldn't open the file\n";
}

Item Level::CreateItem(char c, float line, float col)
{
    Item newItem;
    switch (c)
    {
    case 'c':
        newItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, BLACK, ItemType::coin };
        break;
    default:
        newItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, GREEN, ItemType::shroom };
    }
    return newItem;
}

void Level::DrawItem()
{
    for (int i = 0; i < itemVector.size(); i++)
    {
        DrawRectangleRec(itemVector[i].rect, itemVector[i].color);
        switch (itemVector[i].type)
        {
        case ItemType::coin:
            DrawTexture(CoinTexture, itemVector[i].rect.x, itemVector[i].rect.y, LIGHTGRAY);
            break;
        case ItemType::shroom:
            DrawTexture(ShroomTexture, itemVector[i].rect.x, itemVector[i].rect.y, LIGHTGRAY);
            break;
        default:
            DrawTexture(ShroomTexture, itemVector[i].rect.x, itemVector[i].rect.y, LIGHTGRAY);
        }
    }
}