#pragma once

class Game
{
public:
    int world;
    int currentLevel;
    int totalLevel;
    int unlockLevel;
    int worldTotalLevel;
	/*    int World = 1;
    int Partie = 1;
    int niveauActuel = 1;
    int niveauDebloque = 6;
    int niveauTotalDuMonde = 6;*/
public:
    Game();
    Game(int world, int currentLevel, int totalLevel, int unlockLevel );
    int GetWorld();
    void SetWorld(int c_world);
    const int GetCurrentLevel() const;
    void SetCurrentLevel(int c_level); 

    int GetTotalLevel(); 
    void SetTotalLevel();
    int GetUnlockLevel();
    void SetUnlockLevel(int c_unlocklevel);

};

