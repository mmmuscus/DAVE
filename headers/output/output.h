#include "../system/system.h"

void saveLastScreenArray(char oldS[SCREENROWS][SCREENCOLS], char newS[SCREENROWS][SCREENCOLS]);

void saveLastMenuArray(char oldM[SCREENROWS][MENUCOLS], char newM[SCREENROWS][MENUCOLS]);

void initSolid(char solide[SOLIDCOUNT]);

void initWalkable(char walkablee[WALKABLECOUNT]);

void initWorld(map world[WORLDROWS][WORLDCOLS], char solide[SOLIDCOUNT], char walkablee[WALKABLECOUNT]);
