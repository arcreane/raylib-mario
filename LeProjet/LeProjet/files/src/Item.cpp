#include "Item.h"
#include <vector>

void Item::UpdateItem(Player *p, Level *l)
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

void Item::UseItem(Level *l)
{
    l->score+=1;
    l->RemoveItem(this);
}

bool Item::operator==(const Item& i) const
{
    if (i.rect.x == this->rect.x &&
        i.rect.y == this->rect.y &&
        i.rect.width == this->rect.width &&
        i.rect.height == this->rect.height
    )
        return true;
    else
        return false;
}
