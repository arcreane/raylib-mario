#include "Item.h"
#include <vector>

Item::Item(ItemType t)
{
    rect = { 0 + 25, -800 + 25, 100, 100 };
    for (int i = 0; i<4; i++)
        blocking[i] = 1;
    color = BLANK;
    type = t;
}

void Item::SetRectangle(Rectangle rec)
{
    rect = rec;
}

void Item::UpdateItem(Player *p, PlayableLevel* l)
{
    // Check if the item is in contact with the player
    if (p->position.x >= this->rect.x &&
        p->position.x <= this->rect.x + this->rect.width &&
        p->position.y >= this->rect.y &&
        p->position.y <= this->rect.y + this->rect.height
    )
    {
        this->UseItem(l);
    }
}


bool Item::operator==(const Item& i) const
{
    if (i.type == this->type &&
        i.blocking == this->blocking &&
        i.rect.x == this->rect.x &&
        i.rect.y == this->rect.y &&
        i.rect.width == this->rect.width &&
        i.rect.height == this->rect.height
    )
        return true;
    else
        return false;
}
