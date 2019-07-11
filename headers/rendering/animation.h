#include "../system/system.h"
//#include "../rendering/render.h"

animation initNewAnimation(animation anim, string fileName);

void playAnimation(char console[CONSOLEROWS][CONSOLECOLS], animation anim, int currentFrame, int yRow, int xCol);
