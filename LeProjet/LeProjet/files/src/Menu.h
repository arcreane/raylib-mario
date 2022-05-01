#pragma once
#include "Level.h"
#include <raylib.h>

class Menu : public Level
{
private:
	typedef Level super;
	int world;
	int currentLevel;
	int totalLevel;
	int unlockLevel; // number of unlocked levels
	int envItemsLengthMAPmonde1;
	std::string playerName;
	int coins; // Total number of coins collected

	Texture2D youAreHereTexture;

	Color returnColorToPrint(int i, int unlockLevel, int actuelLevel);

public:
	Menu(LevelManager& levelManager);

	void InitLevel() override;
	void UpdateLevel() override;
	void DrawLevel() override;

	void LoadSave(); // Load the progress of user from a file
	void NextLevel() override;

	// Getter - Setter 
	int GetWorld() const;
	const int GetCurrentLevel() const;
	int GetTotalLevel() const;
	int GetUnlockLevel() const;
	void SetWorld(int c_world);
	void SetCurrentLevel(int c_level);
	void SetTotalLevel(int c_totalLevel);
	void SetUnlockLevel(int c_unlocklevel);
};