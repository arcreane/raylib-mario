#include "Map.h"
#include "raylib.h"
#include "structures.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;


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

EnvItem Map::CreateEnvItem(char c, float line,float col)
{
    EnvItem newEnvItem;
    switch (c)
    {
        case 'a':
            newEnvItem = { { col * 100, -800 + (line * 100), 100, 100 }, {1,1,1,1}, BLACK, ItemType::ground };
            break;
        case 'z':
            newEnvItem = { { col * 100, -800+(line * 100), 100, 100 }, {1,1,1,1}, RED, ItemType::sky };
            break;
        default:
            newEnvItem = { { col * 100, -800+(line * 100), 100, 100 }, {1,1,1,1}, GREEN, ItemType::sky };
    }
    return newEnvItem;
}

void Map::DrawMap()
{
    ClearBackground(backgroundColor);
    Texture2D Ground = LoadTexture("../LeProjet/LeProjet/files/img/BlocTerre100-100.png");

    for (int i = 0; i < mapVector.size(); i++)
    {
        DrawRectangleRec(mapVector[i].rect, mapVector[i].color);
        if (mapVector[i].type == ItemType::ground)
        {
            DrawTexture(Ground, mapVector[i].rect.x, mapVector[i].rect.y, LIGHTGRAY);
        }
    }
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