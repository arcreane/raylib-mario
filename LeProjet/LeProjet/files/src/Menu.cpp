#include "Menu.h"

#include "Camera.h"
#include "LevelManager.h"

Menu::Menu(LevelManager& levelManager)
    :Level(LevelName::menu, levelManager)
{
    currentLevel = 1;
    world = 1;
    totalLevel = 6;
    unlockLevel = 5;
    envItemsLengthMAPmonde1=0;
    player.position = { 20 , 0 };

	youAreHereTexture = LoadTexture("../LeProjet/LeProjet/files/img/YouAreHere2.png");
}

void Menu::InitLevel()
{
	player.speed = 0;
	player.canJump = false;

    camera.target = player.position;
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    map.mapVector = {
        {{ -1000, -1000, 2000, 400 }, {0,0,0,0}, LIGHTGRAY, EnvItemType::sky},
        {{ 0,0, 10000, 200 }, {1,1,1,1}, DARKBROWN, EnvItemType::sky },
        {{ 0, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(1,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 300, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(2,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 600, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(3,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 900, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(4,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 1200, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(5,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 1500, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(6,unlockLevel,currentLevel),EnvItemType::sky}
    };

    envItemsLengthMAPmonde1 = map.mapVector.size();
}

void Menu::UpdateLevel()
{
    float deltaTime = GetFrameTime();

    // Should be updated in a method update map instead of creating all map every loop (frame)
    map.mapVector = {
        {{ -1000, -1000, 2000, 400 }, {0,0,0,0}, LIGHTGRAY, EnvItemType::sky},
        {{ 0,0, 10000, 200 }, {1,1,1,1}, DARKBROWN, EnvItemType::sky },
        {{ 0, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(1,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 300, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(2,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 600, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(3,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 900, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(4,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 1200, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(5,unlockLevel,currentLevel),EnvItemType::sky},
        {{ 1500, 0, 40 , 40 }, {1,1,1,1}, returnColorToPrint(6,unlockLevel,currentLevel),EnvItemType::sky}
    };

    // THIS UPDATE UPDATE THE PLAYER NOT THE MAP
    map.UpdateMAP(&player, map.mapVector.data(), envItemsLengthMAPmonde1, deltaTime, &currentLevel, &unlockLevel);
    cameraUpdaters[2](&camera, &player, map.mapVector.data(), envItemsLengthMAPmonde1, deltaTime, screenWidth, screenHeight);

    if (IsKeyPressed(KEY_B))
    {
        printf("Position de X: %f \nPosition de Y: %f \n ", player.position.x, player.position.y);
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        levelManager->LoadLevel(LevelName::lvl1);
    }
}

void Menu::DrawLevel()
{
    BeginDrawing();

    ClearBackground(LIGHTGRAY);

    // Display data on the screen
    std::string DispCurrentWorld = "Monde : " + std::to_string(world);
    char const* pchar = DispCurrentWorld.c_str();  // use char const* as target 
    std::string DispCurrentLevel = "Niveau : " + std::to_string(currentLevel);
    char const* pchar2 = DispCurrentLevel.c_str();  // use char const* as target type

    DrawText(pchar, 5, 0, 30, BLUE);
    DrawText(pchar2, 5, 40, 30, BLUE);

    BeginMode2D(camera);
    for (int i = 0; i < envItemsLengthMAPmonde1; i++) DrawRectangleRec(map.mapVector[i].rect, map.mapVector[i].color);
    // Rectangle playerRect = { playerMENU.position.x - 20, playerMENU.position.y - 40, 40, 40 };
    // DrawRectangleRec(playerRect, DARKBLUE);
    DrawTexture(youAreHereTexture, player.position.x - 50, player.position.y - 105, LIGHTGRAY);

    for (size_t i = 0; i < this->totalLevel; i++)
    {
        std::string Dispniveauactuel = "Niveau: " + std::to_string(i + 1);
        char const* NiveauActuel = Dispniveauactuel.c_str();  // use char const* as target type

        DrawText(NiveauActuel, -30 + i * 300, 50, 40, BLUE);
    }

    EndMode2D();

    EndDrawing();
}

Color Menu::returnColorToPrint(int i, int unlockLevel, int actuelLevel) {

    if (i == actuelLevel) return YELLOW;
    if (i <= unlockLevel) return GREEN;
    else return RED;
}

int Menu::GetWorld()
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

int Menu::GetTotalLevel()
{
    return totalLevel;
}

void Menu::SetTotalLevel(int c_totalLevel)
{
    this->totalLevel = c_totalLevel;
}

int Menu::GetUnlockLevel()
{
    return unlockLevel;
}

void Menu::SetUnlockLevel(int c_unlocklevel)
{
    this->unlockLevel = c_unlocklevel;
}