#include "Menu.h"
#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Menu::Menu(LevelManager& levelManager)
    :Level(LevelType::menu, LevelType::lvl1, levelManager)
{
    currentLevel = 1;
    world = 1;
    totalLevel = 6;
    unlockLevel = 5;
    envItemsLengthMAPmonde1=0;
    player.SetPosition({ 20 , 0 });
    playerName = "Non defini";
    coins = 0;
	youAreHereTexture = LoadTexture("../LeProjet/LeProjet/files/img/YouAreHere2.png");
    this->music = LoadMusicStream("../LeProjet/LeProjet/files/audio/MainMenu.mp3");
}

void Menu::InitLevel()
{
    super::InitLevel(); // call Init Level of parent class Level to set audio
    player.InitUnit();
    levelCamera->SetCameraTarget(player.GetPosition());
    levelCamera->SetCameraOffset({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });
    
    LoadSave();

    map.SetMapVector(
        {
            {{ -1000, -1000, 2000, 400 }, {0,0,0,0}, LIGHTGRAY, EnvItemType::sky},
            {{ 0,0, 10000, 200 }, {1,1,1,1}, DARKBROWN, EnvItemType::sky },
            {{ 0, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(1,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 300, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(2,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 600, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(3,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 900, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(4,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 1200, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(5,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 1500, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(6,unlockLevel,currentLevel),EnvItemType::sky}
        }
    );

    envItemsLengthMAPmonde1 = (int) map.GetMapVector().size();
}

void Menu::UpdateLevel()
{
    super::UpdateLevel();
    float deltaTime = GetFrameTime();

    map.SetMapVector(
        {
            {{ -1000, -1000, 2000, 400 }, {0,0,0,0}, LIGHTGRAY, EnvItemType::sky},
            {{ 0,0, 10000, 200 }, {1,1,1,1}, DARKBROWN, EnvItemType::sky },
            {{ 0, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(1,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 300, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(2,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 600, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(3,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 900, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(4,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 1200, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(5,unlockLevel,currentLevel),EnvItemType::sky},
            {{ 1500, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(6,unlockLevel,currentLevel),EnvItemType::sky}
        }
    );

    // Update the player in the menu
    map.UpdateMAP(&player, map.GetMapVector().data(), envItemsLengthMAPmonde1, deltaTime, &currentLevel, &unlockLevel);
    levelCamera->SetCameraOption(2);
    levelCamera->cameraUpdaters(&player, map.GetMapVector().data(), envItemsLengthMAPmonde1, deltaTime, screenWidth, screenHeight);

    if (IsKeyPressed(KEY_B))
    {
        printf("Position de X: %f \nPosition de Y: %f \n ", player.GetPosition().x, player.GetPosition().y);
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        StopMusicStream(music);
        NextLevel();
    }
}

void Menu::DrawLevel()
{
    BeginDrawing();
    
    super::DrawLevel();

    ClearBackground(LIGHTGRAY);

    // Display data on the screen
    std::string DispCurrentWorld = "Monde : " + std::to_string(world);
    char const* pchar = DispCurrentWorld.c_str();
    std::string DispCurrentLevel = "Niveau : " + std::to_string(currentLevel);
    char const* pchar2 = DispCurrentLevel.c_str();
    std::string tmp_playerName = "Utilisateur : " + playerName;
    char const* pchar_playerName = tmp_playerName.c_str();
    std::string DispCurrentCoins = "Pieces : " + std::to_string(coins);
    char const* pcharCoins = DispCurrentCoins.c_str();
    
    DrawText(pchar, 5, 0, 30, BLUE);
    DrawText(pchar2, 5, 40, 30, BLUE);
    DrawText(pchar_playerName, 400, 2, 30, BLUE);
    DrawText(pcharCoins, 5, 80, 30, BLUE);
    DrawText("P stopper/reprendre la musique", 950, 0, 20, BLUE);
    DrawText("M relancer la musique", 950, 20, 20, BLUE);

    BeginMode2D(levelCamera->GetCamera());

    for (int i = 0; i < envItemsLengthMAPmonde1; i++) DrawRectangleRec(map.GetMapVector()[i].rect, map.GetMapVector()[i].color);
    
    DrawTexture(youAreHereTexture,(int) player.GetPosition().x - 50,(int) player.GetPosition().y - 105, LIGHTGRAY);

    for (size_t i = 0; i < this->totalLevel; i++)
    {
        std::string Dispniveauactuel = "Niveau: " + std::to_string(i + 1);
        char const* NiveauActuel = Dispniveauactuel.c_str();

        DrawText(NiveauActuel, - 30 + (int) i * 300, 50, 40, BLUE);
    }

    EndMode2D();

    EndDrawing();
}

void Menu::LoadSave()
{
    string line;
    ifstream myfile("../LeProjet/LeProjet/files/sauvegarde.txt");
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

    playerName = tab[0];
    world = stoi(tab[1]);
    unlockLevel = stoi(tab[2]);
    coins = stoi(tab[3]);
}

Color Menu::returnColorToPrint(int i, int unlockLevel, int actuelLevel) {

    if (i == actuelLevel) return YELLOW;
    if (i <= unlockLevel) return GREEN;
    else return RED;
}

void Menu::NextLevel()
{
    switch (currentLevel)
    {
    case 1:
        nextLevelType = LevelType::lvl1;
        break;
    case 2:
        nextLevelType = LevelType::lvl2;
        break;
    case 3:
        nextLevelType = LevelType::lvl3;
        break;
    case 4:
        nextLevelType = LevelType::lvl4;
        break;
    case 5:
        nextLevelType = LevelType::lvl5;
        break;
    case 6:
        nextLevelType = LevelType::lvl6;
        break;
    default:
        nextLevelType = LevelType::lvl1;
    }
    levelManager->LoadLevel(nextLevelType);
}

int Menu::GetWorld() const
{
    return world;
}

void Menu::SetWorld(int c_world)
{
    this->world = c_world;
}

const int Menu::GetCurrentLevel() const
{
    return currentLevel;
}

void Menu::SetCurrentLevel(int c_level)
{
    this->currentLevel = c_level;
}

int Menu::GetTotalLevel() const
{
    return totalLevel;
}

void Menu::SetTotalLevel(int c_totalLevel)
{
    this->totalLevel = c_totalLevel;
}

int Menu::GetUnlockLevel() const
{
    return unlockLevel;
}

void Menu::SetUnlockLevel(int c_unlocklevel)
{
    this->unlockLevel = c_unlocklevel;
}
