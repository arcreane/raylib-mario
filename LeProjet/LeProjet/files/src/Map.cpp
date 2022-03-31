#include "Map.h"
#include "raylib.h"
#include "structures.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

Map::Map()
{
    backgroundColor = SKYBLUE;
    Ground = LoadTexture("../LeProjet/LeProjet/files/img/BlocTerre100-100.png");
    BlocInconnue = LoadTexture("../LeProjet/LeProjet/files/img/Ciel.png");
    Start = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
    Finish = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");

    // TODO : Move in corresponding Level 
    CoinTexture = LoadTexture("../LeProjet/LeProjet/files/img/Coin100-100.png");
    ShroomTexture = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
}

void Map::CreateMap(string filename)
{
    backgroundColor = SKYBLUE;

    char c;   // To read each character from file
    std::vector<char> charVector;
    float line = 0;    // Variable to keep count of each line
    float col = 0;    // Variable to keep count of each colone
    ifstream mFile(filename);
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
                EnvItem item = CreateEnvItem(c,line,col);
                mapVector.push_back(item);
            }
            col++;
        }
        mFile.close();
    }
    else
        cout << "Couldn't open the file\n";
}

void Map::UpdateMAP(Player* player, EnvItem* envItems, int envItemsLength, float delta, int* currentlevel, int* unlockLevel)
{
    int framesCounter = 0;


    if (IsKeyPressed(KEY_LEFT))
    {
        if (*currentlevel > 1)
        {

            player->position.x = player->position.x - 300;
            *currentlevel = *currentlevel - 1;
            printf("%d \n", *currentlevel);
        }
        else printf("\n Tamer \n");
    }


    if (IsKeyPressed(KEY_RIGHT))
    {

        if (*currentlevel < *unlockLevel)
        {

            player->position.x = 20 + (*currentlevel - 1) * 300 + 300;

            *currentlevel = *currentlevel + 1;
            printf("%d \n", *currentlevel);
        }
        else printf("\n Tamer \n");
    }

    /*  if (IsKeyPressed(KEY_RIGHT))
    {

        if (std::exp(g1->GetCurrentLevel()) < std::exp(g1->GetUnlockLevel()))
        {

            player->position.x = 20 + (g1->GetCurrentLevel() - 1) * 300 + 300;
            g1->SetCurrentLevel(g1->GetCurrentLevel() + 1);
            printf("%d \n", g1->GetCurrentLevel());
        }
    }*/
}

void Map::DrawMap()
{
    ClearBackground(backgroundColor);

    for (int i = 0; i < mapVector.size(); i++)
    {
        DrawRectangleRec(mapVector[i].rect, mapVector[i].color);
        switch (mapVector[i].type)
        {
        case EnvItemType::ground:
            DrawTexture(Ground, mapVector[i].rect.x, mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::start:
            DrawTexture(Start, mapVector[i].rect.x, mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::finish:
            DrawTexture(Finish, mapVector[i].rect.x, mapVector[i].rect.y, LIGHTGRAY);
            break;
        default:
            DrawTexture(Ground, mapVector[i].rect.x, mapVector[i].rect.y, LIGHTGRAY);
        }
    }
}


EnvItem Map::CreateEnvItem(char c, float line,float col)
{

    EnvItem newEnvItem;
    switch (c)
    {
        case 'a':
            newEnvItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, BLACK, EnvItemType::ground };
            break;
        case 's':
            newEnvItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, BLACK, EnvItemType::start };
            break;
        case 'f':
            newEnvItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, BLACK, EnvItemType::finish };
            break;
        default:
            newEnvItem = { { col * 100, -800+(line * 100), 100, 100 }, {1,1,1,1}, GREEN, EnvItemType::sky };
    }
    return newEnvItem;
}


void Map::ReadItems(std::string filename)
{
    char c;   // To read each character from file
    std::vector<char> charVector;
    float line = 0;    // Variable to keep count of each line
    float col = 0;    // Variable to keep count of each colone
    ifstream mFile(filename);
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
        cout << "Couldn't open the file\n";
}

Item Map::CreateItem(char c, float line, float col)
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

void Map::DrawItem()
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