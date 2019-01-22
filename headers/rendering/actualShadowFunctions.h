#include "../system/system.h"

koordinate getPov(koordinate pov, mob playr, double heigt, double widt);

line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow);

rectangle getRectangleEdges(koordinate pov, int top, int bottom, int right, int left);

bool isLineOverLine(line e, double middleOfFirstSolidYRow, double middleOfFirstSolidXCol);

bool isUnderLine(line e, int solidYRow, int solidXCol);

bool isOverLine(line e, int solidYRow, int solidXCol);

bool isBetweenLines (line a, line b, int yRow, int xCol);

bool isPlayerNextToRectangle(koordinate pov, int top, int bottom, int right, int left);

bool isPlayerOverOrUnderRectangle(koordinate pov, int top, int bottom, int right, int left);

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left);

line makeLineNull(line e);

// secon d megoldas maybe lets see

line getLineOfSight(koordinate pov, int top, int bottom, int right, int left, line firstLine, bool doesFirstLineExist);

edgeLines getEdges(koordinate pov, int top, int bot, int right, int left);

line getFirstLine(koordinate pov, int top, int bot, int right, int left);

line getSecondLine(koordinate pov, int top, int bot, int right, int left);

edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left);

bool isInShadow(line a, line b, int yRow, int xCol, koordinate pov, int top, int bot, int right, int left);
