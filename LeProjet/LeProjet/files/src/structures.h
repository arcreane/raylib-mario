#pragma once
#include "raylib.h"
#include "raymath.h"

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;