#pragma once
#include "Map.h"
#include "Player.h"
#include "LevelManager.h"

//define

#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

class Game
{
public:
    //Cleaning du main
    
    //variable utilitaire, mais qu'on pourra déplacer comme vous voulez
    int world;
    int currentLevel;
    int totalLevel;
    int unlockLevel;
    Map* gameMap;
    LevelManager* levelManager;
   /* Player player;
    Player player2;*/
public:
    //Init
    Game();
    Game(int world, int currentLevel, int totalLevel, int unlockLevel );
    ~Game();

    //Start 
    void start();
    //Getter - Setter 
    int GetWorld();
    void SetWorld(int c_world);
    const int GetCurrentLevel() const;
    void SetCurrentLevel(int c_level); 
    int GetTotalLevel(); 
    void SetTotalLevel();
    int GetUnlockLevel();
    void SetUnlockLevel(int c_unlocklevel);

    void UpdateMAPmonde1(Player* player, EnvItem* envItems, int envItemsLength, float delta, Game* g1);
};

