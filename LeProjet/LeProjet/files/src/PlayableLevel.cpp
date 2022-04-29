#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include "PlayableLevel.h"
#include "Coin.h"
#include "UpMushroom.h"
#include "Goomba.h"
#include "Koopa.h"
#include "FlyingBomb.h"

using namespace std;

PlayableLevel::PlayableLevel(LevelType levelType, LevelType nextLevelType, LevelManager& levelManager)
	:Level(levelType, nextLevelType, levelManager)
{
    this->score = 0;
    this->has_fallen = false;
    this->gameOver = false;
    this->framesCounter = 0;
    this->framesMax = 300 * 60;
}

PlayableLevel::~PlayableLevel()
{
    ClearItems();
    ClearEnemies();
}

void PlayableLevel::InitLevel()
{ 
    // Empty the vectors of items and enemies
    ClearItems();
    ClearEnemies();
    switch (levelType)
    {
    case LevelType::lvl1:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");

        // Create Enemies and add them to the vector of enemies in the level
        enemies.push_back(new Goomba(700, 0, 700, 900));
        enemies.push_back(new Koopa(500, 0, 500, 700));
        enemies.push_back(new FlyingBomb(1000, 0, 0, -200));
        break;
    case LevelType::lvl2:
        map.CreateMap("../LeProjet/LeProjet/files/map2.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map2.txt");

        break;
    case LevelType::lvl3:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
        break;
    case LevelType::lvl4:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
        break;
    case LevelType::lvl5:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
        break;
    case LevelType::lvl6:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
        break;
    default:
        map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
        this->ReadItems("../LeProjet/LeProjet/files/items_map1.txt");
    }

    score = 0;
    player.SetLives(2);
    has_fallen = false;
    gameOver = false;

    player.SetPosition(map.GetStartPosition());
    levelCamera->SetCameraOption(1);

    framesCounter = 0;
    framesMax = 300 * 60;
}

void PlayableLevel::UpdateLevel()
{
    framesCounter++;
    float deltaTime = GetFrameTime();
    int levelFinished = player.UpdateUnit(map.GetMapVector().data(), map.GetMapVector().size(), deltaTime);

    // Check conditions to end level or reduce lives
    if (levelFinished == 1)
    {
        SaveAfterLevelFinished();
        NextLevel();
    }
    if (gameOver)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        levelManager->LoadLevel(LevelType::menu);
    }
    if (player.GetPosition().y > 200) // Player fall from the map 
    {
        player.SetLives(player.GetLives() - 1);
        has_fallen = true;
        RespawnPlayer();
    }
    if (player.GetLives() < 0) gameOver = true;

    levelCamera->cameraUpdaters(&player, map.GetMapVector().data(), map.GetMapVector().size(), deltaTime, screenWidth, screenHeight);

    // Update enemies in the level
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->UpdateUnit(map.GetMapVector().data(), map.GetMapVector().size(), deltaTime);
        enemies[i]->DetectPlayer(&player, this);
    }

    // Update items in the level
    for (int i = 0; i < itemVector.size(); i++)
    {
        itemVector[i]->UpdateItem(&player, this);
    }

    // Check key pressed by user
    if (IsKeyPressed(KEY_I))
    {
        levelCamera->SetCameraOption(levelCamera->GetCameraOption() +1);
        if (levelCamera->GetCameraOption() == 6)
            levelCamera->SetCameraOption(0);
    }
    if (IsKeyPressed(KEY_R))
    {
        RespawnPlayer(); // Respawn at start bloc of the Level
    }
    if (IsKeyPressed(KEY_B))
    {
        printf("Position de X: %f \nPosition de Y: %f \n ", player.GetPosition().x, player.GetPosition().y);
    }
    if (IsKeyPressed(KEY_N))
    {
        levelManager->LoadLevel(LevelType::menu);
    }
}

void PlayableLevel::DrawLevel()
{
    BeginDrawing();

    BeginMode2D(levelCamera->GetCamera());

    map.DrawMap();
    DrawItems();
    DrawEnemies();
    player.DrawUnit();

    EndMode2D();

    std::string DispCurrentLevel = "Temps restant: " + std::to_string((framesMax / 60) - (framesCounter / 60));
    char const* Game3_time = DispCurrentLevel.c_str();  //use char const* as target type
    std::string tmp_score = "Score: " + std::to_string(this->score);
    char const* Level_score = tmp_score.c_str();
    std::string tmp_lives = "Vies: " + std::to_string(player.GetLives());
    char const* Level_lives = tmp_lives.c_str();
    char const* Level_name = this->levelName.c_str();

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

void PlayableLevel::DrawEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->DrawUnit();
    }
}

void PlayableLevel::ClearEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
    enemies.clear();
}

void PlayableLevel::RemoveEnemy(Enemy* enemy)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemy == enemies[i])
            enemies.erase(enemies.begin() + i);
    }
}

void PlayableLevel::RespawnPlayer()
{
    levelCamera->SetCameraZoom(1.0f);
    player.SetPosition(map.GetStartPosition());
}

void PlayableLevel::ReadItems(std::string filename)
{
    char c;   // To read each character from file
    std::vector<char> charVector;
    float line = 0;
    float col = 0;
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

Item* PlayableLevel::CreateItem(char c, float line, float col)
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

void PlayableLevel::DrawItems()
{
    for (int i = 0; i < itemVector.size(); i++)
    {
        itemVector[i]->DrawItem();
    }
}

void PlayableLevel::RemoveItem(Item* item)
{
    // Delete the item from the vector of items in the Level
    for (int i = 0; i < itemVector.size(); i++)
    {
        if (item == itemVector[i]) // surcharge de l'op�rateur == dans item.cpp
            itemVector.erase(itemVector.begin() + i);
    }
}

void PlayableLevel::ClearItems()
{
    for (int i = 0; i < itemVector.size(); i++)
    {
        delete itemVector[i];
    }
    itemVector.clear();
}

void PlayableLevel::SaveAfterLevelFinished()
{
    //load save 
    string line;
    ifstream myfile("../LeProjet/LeProjet/files/sauvegarde.txt");
    //create a tab of string
    string tab[4];
    int i = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            tab[i] = line;
            i++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    //Save

     // si le niveau à lancé est le nombre de unlock level, du coup on rentre dans la condition
    LevelType levelType = this->levelType;
    int currentLevelNumber;
    switch (levelType)
    {
    case LevelType::lvl1:
        currentLevelNumber = 1;
        break;
    case LevelType::lvl2:
        currentLevelNumber = 2;
        break;
    case LevelType::lvl3:
        currentLevelNumber = 3;
        break;
    case LevelType::lvl4:
        currentLevelNumber = 4;
        break;
    case LevelType::lvl5:
        currentLevelNumber = 5;
        break;
    case LevelType::lvl6:
        currentLevelNumber = 6;
        break;
    default:
        currentLevelNumber = 0;
    }

    if (stoi(tab[2]) == currentLevelNumber && currentLevelNumber <6) {
        int newUnlockLevel = stoi(tab[2]) + 1;
        tab[2] = to_string(newUnlockLevel);
    }

    int newCoin = stoi(tab[3]) + score;
    tab[3] = to_string(newCoin);
    printf("%d", newCoin);

    fstream my_file;
    my_file.open("../LeProjet/LeProjet/files/sauvegarde.txt", ios::out);
    if (!my_file) {
        cout << "File not created!";
    }
    else {
        cout << "File created successfully!" << endl;
        my_file << tab[0] << endl;
        my_file << tab[1] << endl;
        my_file << tab[2] << endl;
        my_file << tab[3] << endl;
        my_file.close();
    }
    //printf("\n resultat : \n %s\n", tab[3]);
}

void PlayableLevel::SetScore(int score)
{
    this->score = score;
}

int PlayableLevel::GetScore()
{
    return score;
}