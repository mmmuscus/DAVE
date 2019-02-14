#include "../system/system.h"

//SET CURRENT FOV

void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS]);

void setCurrentFov(mob playr, fov toBecomeCurrentFov[FOVROWS][FOVCOLS], fov r[FOVROWS][FOVCOLS], fov l[FOVROWS][FOVCOLS], fov u[FOVROWS][FOVCOLS], fov d[FOVROWS][FOVCOLS], fov ru[FOVROWS][FOVCOLS], fov rd[FOVROWS][FOVCOLS], fov lu[FOVROWS][FOVCOLS], fov ld[FOVROWS][FOVCOLS]);

// GET PLAYER POS IN CURRENT FOV

mob getPlayerPosInFov(mob playr, mob fovPlayr);

//GET FELT�TEL FOR FOV TO DISPLAY THE ENTRIE FOV JEEEE

void addFovInfoToMap(map world[WORLDROWS][WORLDCOLS], mob playr, mob fovPlayr, fov fov[FOVROWS][FOVCOLS]);

//actual shadow functions

koordinate getPov(koordinate pov, mob playr);

line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow);

bool isUnderLine(line e, int solidYRow, int solidXCol);

bool isOverLine(line e, int solidYRow, int solidXCol);

bool isBetweenLines(line a, line b, int yRow, int xCol);

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left);

// secon d megoldas maybe lets see

edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left);

void shadowFunction(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow, koordinate pov, edgeLines edg);

bool isBesideNotSolidInView(map world[WORLDROWS][WORLDCOLS], int xCol, int yRow);

void mapIsEdgeCalculation(map world[WORLDROWS][WORLDCOLS], int cameraRow, int cameraCol);
