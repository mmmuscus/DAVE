#include "../system/system.h"

void goTo (int row, int column);

void clearScreen();

//void renderScreen(char oldS[SCREENROWS][SCREENCOLS], char newS[SCREENROWS][SCREENCOLS]);
//
//void renderMenu(char oldM[SCREENROWS][MENUCOLS], char newM[SCREENROWS][MENUCOLS]);

void renderConsole(char oldC[CONSOLEROWS][CONSOLECOLS], char newC[CONSOLEROWS][CONSOLECOLS]);

void calculateScreen(map world[WORLDROWS][WORLDCOLS], char console[CONSOLEROWS][CONSOLECOLS], /*char screen[SCREENROWS][SCREENCOLS],*/ int cameraRow, int cameraCol);
