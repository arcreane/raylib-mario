#pragma once

class Game
{
public:
    //Cleaning du main
    
    //variable utilitaire, mais qu'on pourra déplacer comme vous voulez
    int world;
    int currentLevel;
    int totalLevel;
    int unlockLevel;
   /* Player player;
    Player player2;*/
public:
    //Init
    Game();
    Game(int world, int currentLevel, int totalLevel, int unlockLevel );

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
};

