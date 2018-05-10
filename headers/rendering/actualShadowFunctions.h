#include "../system/system.h"

koordinate getPov(koordinate pov, mob playr, double heigt, double widt);

line getLineEquation(line e, double aXCol, double aYRow, double bXCol, double bYRow);

line getLowerLine(line e, koordinate pov, int solidCol, int solidRow, double heigt, double widt);

line getUpperLine(line e, koordinate pov, int solidCol, int solidRow, double heigt, double widt);

bool isPointOver(line e, double row, double col);

bool isPointUnder(line e, double row, double col);

//actual shadowfunctions

bool isWhollyInShadow(line overLine, line underLine, int row, int col, double heigt, double widt);

//bool isBlockedFromLight(line e, bool inShadow, koordinate pov, int row, int col, double heigt, double widt);
