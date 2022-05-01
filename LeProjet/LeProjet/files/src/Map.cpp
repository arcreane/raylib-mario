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
    Bricks = LoadTexture("../LeProjet/LeProjet/files/img/BrickBlock100-100.png");
    Dirt = LoadTexture("../LeProjet/LeProjet/files/img/BlockDirt100-100.png");
    Classic = LoadTexture("../LeProjet/LeProjet/files/img/ClassicBlock100-100.png");
    Surprise = LoadTexture("../LeProjet/LeProjet/files/img/SurpriseBloc100-100.png");
    Pipe = LoadTexture("../LeProjet/LeProjet/files/img/pipe100-100.png");
    PipeBas = LoadTexture("../LeProjet/LeProjet/files/img/pipeBas100-100.png");
    BlocInconnue = LoadTexture("../LeProjet/LeProjet/files/img/Ciel.png");
    Start = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
    Finish = LoadTexture("../LeProjet/LeProjet/files/img/Goldbrickblock100-100.png");
    Castle = LoadTexture("../LeProjet/LeProjet/files/img/Castel100-100.png");
    Poteau = LoadTexture("../LeProjet/LeProjet/files/img/Poteau100-100.png");
    Flag = LoadTexture("../LeProjet/LeProjet/files/img/Flag100-100.png");
    Nuage = LoadTexture("../LeProjet/LeProjet/files/img/Nuage100-100.png");
    Buisson = LoadTexture("../LeProjet/LeProjet/files/img/Buisson100-100.png");
    Stone = LoadTexture("../LeProjet/LeProjet/files/img/Grey100-100.png");
    Lava = LoadTexture("../LeProjet/LeProjet/files/img/Lava100-100.png");
    Bedrock = LoadTexture("../LeProjet/LeProjet/files/img/Bedrock100-100.png");
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

            x = (float) (20 + (*currentlevel - 1) * 300 + 300);
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
            DrawTexture(Ground, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::dirt:
            DrawTexture(Dirt, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::brick:
            DrawTexture(Bricks, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::classic:
            DrawTexture(Classic, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::surprise:
            DrawTexture(Surprise, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::pipe:
            DrawTexture(Pipe, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::pipeB:
            DrawTexture(PipeBas, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::start:
            DrawTexture(Start, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::finish:
            DrawTexture(Finish, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::castle:
            DrawTexture(Castle, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::poteau:
            DrawTexture(Poteau, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::flag:
            DrawTexture(Flag, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::nuage:
            DrawTexture(Nuage, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::buisson:
            DrawTexture(Buisson, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::stone:
            DrawTexture(Stone, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::lava:
            DrawTexture(Lava, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        case EnvItemType::bedrock:
            DrawTexture(Bedrock, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
            break;
        default:
            DrawTexture(Ground, (int) mapVector[i].rect.x, (int) mapVector[i].rect.y, LIGHTGRAY);
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
        case 'd':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::dirt };
            break;
        case 'b':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::brick };
            break;
        case 'c':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::classic };
            break;
        case 't':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::surprise };
            break;
        case 'p':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::pipe };
            break;
        case 'q':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::pipeB };
            break;
        case 's':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::start };
            startPosition = { col * 100 + 50, -800 + (line * 100) -10};
            break;
        case 'f':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::finish };
            break;
        case 'j':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::castle };
            break;
        case 'x':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::poteau };
            break;
        case 'g':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::flag };
            break;
        case 'n':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::nuage };
            break;
        case 'm':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::buisson };
            break;
        case 'o':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::stone };
            break;
        case 'v':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {0,0,0,0}, BLACK, EnvItemType::lava };
            break;
        case 'k':
            newEnvItem = { { col * 100, -800 + (line * 100), 100 + 25, 100 + 25}, {1,1,1,1}, BLACK, EnvItemType::bedrock };
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

void Map::SetBackGroundColor(Color backgroundColor)
{
    this->backgroundColor = backgroundColor;
}
