#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <iostream>
#include <string>


typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;