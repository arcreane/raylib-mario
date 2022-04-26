#include "Level.h"
#include "camera.h"
#include "Coin.h"
#include "Goomba.h"
#include "Koopa.h"
#include "UpMushroom.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

Level::Level(LevelName name, LevelName nextLevelName, LevelManager& levelManager, std::string nameDisplayed)
{
	this->name = name;
    this->nextLevelName = nextLevelName;
	this->levelManager = &levelManager;
    this->nameDisplayed = nameDisplayed;
    this->score = 0;
    this->lives = 2;
    this->has_fallen = false;
    this->gameOver = false;
    

	camera = { 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	cameraOption = 0;

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

    //ENEMY à classer
    enemyAmount = 0;
    previousTime = 0.0;
    currentTime = GetTime();
    deltaTime = 0.0f;
    previousTime2 = 0.0;
    currentTime2 = GetTime();
    deltaTime2 = 0.0f;
    direction = "goings";
    direction2 = "goings";

    marioTexture = LoadTexture("../LeProjet/LeProjet/files/img/mario50-50.png");
    goombaTexture = LoadTexture("../LeProjet/LeProjet/files/img/goomba_retour.png");
    goombaTexture2 = LoadTexture("../LeProjet/LeProjet/files/img/goomba_alle.png");
    koopaTexture = LoadTexture("../LeProjet/LeProjet/files/img/koopa_alle.png");
    koopaTexture2 = LoadTexture("../LeProjet/LeProjet/files/img/koopa_retour.png");
    
    // Item Texture
    CoinTexture = LoadTexture("../LeProjet/LeProjet/files/img/Coin50-50.png");
    UpMushroomTexture = LoadTexture("../LeProjet/LeProjet/files/img/upMushroom50-50.png");
}

Level::~Level()
{
    ClearItems();
}

void Level::InitLevel()
{
    // Empty the vector of items
    ClearItems();
    switch (name)
	{
	case LevelName::lvl1:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
        
        // Create Enemies and add them to the vector of enemies in the level
        enemies.push_back(new Goomba(70, -15, 70, 500));
        enemies.push_back(new Goomba(700, -15, 700, 900));
        enemies.push_back(new Koopa(100, -15, 80, 400));
        enemies.push_back(new Koopa(500, -15, 500, 700));
		break;
	case LevelName::lvl2:
		map.CreateMap("../LeProjet/LeProjet/files/map2.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map2.txt");
        
		break;
	case LevelName::lvl3:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
		break;
	case LevelName::lvl4:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
		break;
	case LevelName::lvl5:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
		break;
	case LevelName::lvl6:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
		break;
	default:
		map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
	}

    score = 0;
    lives = 2;
    has_fallen = false;
    gameOver = false;

    camera.target = player.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    player.position = map.startPosition;
    player.speed = 0;
    player.canJump = false;

    framesCounter = 0;
    framesMax = 300 * 60;
}

void Level::UpdateLevel()
{
    framesCounter++;
    float deltaTime = GetFrameTime();
    int levelFinished = player.UpdatePlayer(map.mapVector.data(), map.mapVector.size(), deltaTime);
    
    // Check conditions to end level or reduce lives
    if (levelFinished == 1)
    {
        player.SetNumberOfCoins(score);
        //levelManager->LoadLevel(LevelName::menu);
        NextLevel();
    }
    if (gameOver)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        player.SetNumberOfCoins(score);
        levelManager->LoadLevel(LevelName::menu);
    }
    if (player.position.y > 200) // Player fall from the map 
    {
        lives -= 1;
        has_fallen = true;
        camera.zoom = 1.0f;
        player.position = map.startPosition;
    }
    if (lives < 0) gameOver = true;

    cameraUpdaters[cameraOption](&camera, &player, map.mapVector.data(), map.mapVector.size(), deltaTime, screenWidth, screenHeight);

    // Update enemies in the level
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->UpdateEnemy();
    }
    
    // Update items in the level
    for (int i =0;i<itemVector.size(); i++)
    {
        itemVector[i]->UpdateItem(&player, this);
    }

    // Check key pressed by user
    if (IsKeyPressed(KEY_I))
    {
        cameraOption++;
        if (cameraOption == 6)
            cameraOption = 0;
    }
    if (IsKeyPressed(KEY_R)) // Respawn at start of Level
    {
        camera.zoom = 1.0f;
        player.position = map.startPosition;
    }
    if (IsKeyPressed(KEY_B))
    {
        printf("Position de X: %f \nPosition de Y: %f \n ", player.position.x, player.position.y);
    }
    if (IsKeyPressed(KEY_N))
    {
        player.SetNumberOfCoins(score);
        player.GetNumberOfCoins();
        levelManager->LoadLevel(LevelName::menu);
    }
}

void Level::DrawLevel()
{
    BeginDrawing();

    BeginMode2D(camera);

    map.DrawMap();
    DrawItem();
    DrawEnemies();
    DrawTexture(marioTexture, player.position.x - 20, player.position.y - 50, LIGHTGRAY);

    EndMode2D();

    std::string DispCurrentLevel = "Temps restant: " + std::to_string((framesMax / 60) - (framesCounter / 60));
    char const* Game3_time = DispCurrentLevel.c_str();  //use char const* as target type
    std::string tmp_score = "Score: " + std::to_string(this->score);
    char const* Level_score = tmp_score.c_str();
    std::string tmp_lives = "Vies: " + std::to_string(this->lives);
    char const* Level_lives = tmp_lives.c_str();
    char const* Level_name = this->nameDisplayed.c_str();

    DrawText(Game3_time, 5, 0, 30, RED);
    DrawText(Level_lives, 5, 40, 30, RED);
    DrawText(Level_name, 630, 0, 30, RED);
    DrawText(Level_score, 630, 40, 30, RED);
    DrawText("Controls:", 20, 70, 10, BLACK);
    DrawText("- Right/Left to move", 40, 90, 10, DARKGRAY);
    DrawText("- Space to jump", 40, 110, 10, DARKGRAY);
    DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 130, 10, DARKGRAY);

    if (gameOver)
    {
        DrawText("GAME OVER", 300, 200, 100, RED);
    }

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
                Item* item = CreateItem(c, line, col);
                itemVector.push_back(item);
            }
            col++;
        }
        mFile.close();
    }
    else
        std::cout << "Couldn't open the file\n";
}

Item* Level::CreateItem(char c, float line, float col)
{
    Item* newItem;
    Rectangle newRect = { col * 100 + 25, -800 + (line * 100) + 25, 100, 100 };
    switch (c)
    {
    case 'c':
        newItem = new Coin();
        break;
    case 's':
        newItem = new UpMushroom();
        break;
    default:
        newItem = new Coin();
    }
    newItem->SetRectangle(newRect);
    return newItem;
}

void Level::DrawItem()
{
    for (int i = 0; i < itemVector.size(); i++)
    {
        DrawRectangleRec(itemVector[i]->rect, itemVector[i]->color);
        switch (itemVector[i]->type)
        {
        case ItemType::coin:
            DrawTexture(CoinTexture, itemVector[i]->rect.x, itemVector[i]->rect.y, LIGHTGRAY);
            break;
        case ItemType::upMushroom:
            DrawTexture(UpMushroomTexture, itemVector[i]->rect.x, itemVector[i]->rect.y, LIGHTGRAY);
            break;
        default:
            DrawTexture(UpMushroomTexture, itemVector[i]->rect.x, itemVector[i]->rect.y, LIGHTGRAY);
        }
    }
}

void Level::RemoveItem(Item *item)
{
    // Delete the item from the vector of items in the Level
    for (int i = 0; i < itemVector.size(); i++)
    {
        if (item == itemVector[i]) // surcharge de l'opérateur == dans item.cpp
            itemVector.erase(itemVector.begin() + i);
    }
}

void Level::ClearItems()
{
    for (int i = 0; i < itemVector.size(); i++)
    {
        delete itemVector[i];
    }
    itemVector.clear();
}

void Level::NextLevel()
{
    this->levelManager->LoadLevel(this->nextLevelName);
}

void Level::DrawEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->DrawEnemy();
    }
}
