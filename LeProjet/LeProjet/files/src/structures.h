#pragma once
#include "raylib.h"
#include "raymath.h"

enum class EnvItemType { ground, sky, start, finish, dirt, brick, classic, surprise, pipe, pipeB, castle, poteau, flag, nuage, buisson, stone, lava, bedrock };

typedef struct EnvItem {
    Rectangle rect;
    int blocking[4]; // {top, right, bottom, left}
    Color color;
    EnvItemType type;
} EnvItem;

