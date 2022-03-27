#pragma once
#include "raylib.h"
#include "raymath.h"

enum class ItemType { ground, sky };

typedef struct EnvItem {
    Rectangle rect;
    int blocking[4];
    Color color;
    ItemType type;
} EnvItem;

//ENEMY à classer
typedef struct Enemy {
    Rectangle rec;
    bool active;
    Color color;
    Vector2 position;
}Enemy;

