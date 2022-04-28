#include "Item.h"
#include <vector>

Item::Item(ItemType t)
{
    rect = { 0 + 25, -800 + 25, 100, 100 };
    for (int i = 0; i<4; i++)
        blocking[i] = 1;
    color = BLANK;
    type = t;
    itemTexture = LoadTexture("../LeProjet/LeProjet/files/img/coin50-50.png");
}

void Item::SetRectangle(Rectangle rec)
{
    rect = rec;
}

void Item::UpdateItem(Player *p, PlayableLevel* l)
{
    // Check if the item is in contact with the player
    if (p->GetPosition().x >= this->rect.x &&
        p->GetPosition().x <= this->rect.x + this->rect.width &&
        p->GetPosition().y >= this->rect.y &&
        p->GetPosition().y <= this->rect.y + this->rect.height
    )
    {
        this->UseItem(p,l);
    }
}

void Item::DrawItem()
{
    DrawTexture(itemTexture,rect.x,rect.y, LIGHTGRAY);
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
