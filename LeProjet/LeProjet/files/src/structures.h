#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

//ENEMY à classer
typedef struct Enemy {
    Rectangle rec;
    bool active;
    Color color;
    Vector2 position;
}Enemy;

