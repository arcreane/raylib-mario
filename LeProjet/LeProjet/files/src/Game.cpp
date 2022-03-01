#include "Game.h"
#include <cstring>
#include "structures.h"

//création de base
Game::Game()
{
	this->currentLevel = 1;
	this->world = 1;
	this->totalLevel = 6;
	this->unlockLevel = 1;

}

//pour faire nos test
Game::Game(int world, int currentLevel, int totalLevel, int unlockLevel)
{
	this->currentLevel = currentLevel;
	this->world = world;
	this->totalLevel = totalLevel;
	this->unlockLevel = unlockLevel;

}

void Game::start()
{

}











//--------------------
//
//--------------------
int Game::GetWorld()
{
	return world;
}

void Game::SetWorld(int c_world)
{
	this->world = c_world;
}

const int Game::GetCurrentLevel() const
{
	return currentLevel;
}

void Game::SetCurrentLevel(int c_level)
{
	this->currentLevel = c_level;
}

int Game::GetTotalLevel()
{
	return  totalLevel;
}

void Game::SetTotalLevel()
{
	this->totalLevel = 6;
}

int Game::GetUnlockLevel()
{
	return unlockLevel;
}

void Game::SetUnlockLevel(int c_unlocklevel)
{
	this->unlockLevel = c_unlocklevel;
}

