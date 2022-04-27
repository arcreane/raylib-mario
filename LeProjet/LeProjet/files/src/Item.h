#pragma once
#include "structures.h"
#include "Player.h"
#include "PlayableLevel.h"

enum class ItemType { coin, upMushroom };
class PlayableLevel;

class Item
{
public:
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    ItemType type;

    Item(ItemType t);
    void SetRectangle(Rectangle rec);
    void UpdateItem(Player *p, PlayableLevel* l);
    virtual void UseItem(PlayableLevel* l) = 0;  // pure virtual function
    bool operator==(const Item &i) const;
};

