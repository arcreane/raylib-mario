#pragma once
#include "raylib.h"
#include "raymath.h"

enum class EnvItemType { ground, sky, start, finish };

typedef struct EnvItem {
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    EnvItemType type;
} EnvItem;

//ENEMY à classer
/*typedef struct Enemy {
    Rectangle rec;
    bool active;
    Color color;
    Vector2 position;
}Enemy;*/

