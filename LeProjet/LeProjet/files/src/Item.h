#pragma once
#include "structures.h"
#include "Player.h"
#include "PlayableLevel.h"

enum class ItemType { coin, upMushroom };
class PlayableLevel;

class Item
{
protected:
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    ItemType type;
    Texture2D itemTexture;

    virtual void UseItem(Player* p, PlayableLevel* l) = 0;  // pure virtual function
    bool operator==(const Item& i) const;

public:
    Item(ItemType t);
    
    void UpdateItem(Player *p, PlayableLevel* l);
    void DrawItem();

    void SetRectangle(Rectangle rec);
};

