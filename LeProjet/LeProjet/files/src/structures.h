#pragma once
#include "raylib.h"
#include "raymath.h"

enum class EnvItemType { ground, sky, start, finish, dirt, brick, classic, surprise, pipe, pipeB, castle, poteau, flag, nuage, buisson, stone, lava, bedrock };

typedef struct EnvItem {
    Rectangle rect;
    int blocking[4]; // blocking from {top, right, bottom, left} 0 = player can go through, 1 = player can't go through
    Color color;
    EnvItemType type;
} EnvItem;

