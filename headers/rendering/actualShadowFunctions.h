#include "../system/system.h"

koordinate getPov(koordinate pov, mob playr, double heigt, double widt);

line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow);

bool isUnderLine(line e, int solidYRow, int solidXCol);

bool isOverLine(line e, int solidYRow, int solidXCol);

bool isBetweenLines(line a, line b, int yRow, int xCol);

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left);

// secon d megoldas maybe lets see

edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left);
