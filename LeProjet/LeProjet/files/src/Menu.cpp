#include "Menu.h"
Color returnColorToPrint(int i, int* unlockLevel, int* actuelLevel) {

    if (i == *actuelLevel) return YELLOW;
    if (i <= *unlockLevel)return GREEN;
    else return RED;
}