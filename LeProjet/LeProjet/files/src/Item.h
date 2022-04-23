#pragma once
#include "structures.h"
#include "Player.h"
#include "Level.h"

enum class ItemType { coin, shroom };
class Level;

class Item
{
public:
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    ItemType type;

    void UpdateItem(Player *p, Level *l);
    void UseItem(Level *l);
    bool operator==(const Item &i) const;
};

