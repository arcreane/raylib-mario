#include "Map.h"
#include "raylib.h"
#include "structures.h"
#include <iostream>


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