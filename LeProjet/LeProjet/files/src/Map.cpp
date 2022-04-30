#include "Map.h"
#include "raylib.h"
#include "structures.h"
#include <iostream>
#include <fstream>

using namespace std;

Map::Map()
{
    backgroundColor = SKYBLUE;
    startPosition = { 120 , -10 };
    Ground = LoadTexture("../LeProjet/LeProjet/files/img/BlocTerre100-100.png");
    BlocInconnue = LoadTexture("../LeProjet/LeProjet/files/img/Ciel.png");
    Start = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
    Finish = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
}

void Map::CreateMap(string filename)
{
    backgroundColor = SKYBLUE;
    mapVector.clear();

    char c;   // character
    std::vector<char> charVector;
    float line = 0;
    float col = 0;
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
    float x;
    float y;
    if (IsKeyPressed(KEY_LEFT))
    {
        if (*currentlevel > 1)
        {

            x = player->GetPosition().x;
            y = player->GetPosition().y;
            player->SetPosition({ x - 300,y });
            *currentlevel = *currentlevel - 1;
            printf("%d \n", *currentlevel);
        }
        else printf("\n Action Impossible \n");
    }


    if (IsKeyPressed(KEY_RIGHT))
    {

        if (*currentlevel < *unlockLevel)
        {

            x = 20 + (*currentlevel - 1) * 300 + 300;
            y = player->GetPosition().y;
            player->SetPosition({ x,y });

            *currentlevel = *currentlevel + 1;
            printf("%d \n", *currentlevel);
        }
        else printf("\n Niveau non debloque \n");
    }
}

void Map::DrawMap()
{
    ClearBackground(backgroundColor);

    for (int i = 0; i < mapVector.size(); i++)
    {
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
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 +25 }, {1,1,1,1}, BLACK, EnvItemType::ground };
            break;
        case 's':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::start };
            startPosition = { col * 100 + 50, -800 + (line * 100) -10};
            break;
        case 'f':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::finish };
            break;
        default:
            newEnvItem = { { col * 100, -800+(line * 100), 100 + 25, 100 + 25 }, {1,1,1,1}, GREEN, EnvItemType::sky };
    }
    return newEnvItem;
}

Vector2 Map::GetStartPosition() const
{
    return startPosition;
}

std::vector<EnvItem> Map::GetMapVector() const
{
    return mapVector;
}

void Map::SetMapVector(std::vector<EnvItem> mapVector)
{
    this->mapVector = mapVector;
}
