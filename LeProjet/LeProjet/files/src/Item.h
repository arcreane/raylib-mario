#pragma once
#include "structures.h"

enum class ItemType { coin, shroom };

class Item
{
public:
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    ItemType type;
};

