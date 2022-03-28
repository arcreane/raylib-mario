#include "Level.h"

Level::Level(LevelName name)
{
	switch (name)
	{
	case LevelName::menu:
		CreateMenu();
		break;
	case LevelName::lvl1:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl2:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl3:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl4:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl5:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	case LevelName::lvl6:
		CreateLevel("../LeProjet/LeProjet/files/map1.txt");
		break;
	default:
		CreateMenu();
	}
}

void Level::CreateMenu()
{

}

void Level::CreateLevel(std::string filename)
{
	map.CreateMap("../LeProjet/LeProjet/files/map1.txt");
}
