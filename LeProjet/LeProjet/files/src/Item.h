#pragma once
#include "structures.h"
#include "Player.h"
#include "Level.h"

enum class ItemType { coin, upMushroom };
class Level;

class Item
{
public:
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    ItemType type;

    Item(ItemType t);
    void SetRectangle(Rectangle rec);
    void UpdateItem(Player *p, Level *l);
    virtual void UseItem(Level *l) = 0;  // pure virtual function
    bool operator==(const Item &i) const;
};

