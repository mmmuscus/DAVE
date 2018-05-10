#include "../system/system.h"

//INITIALISE THE STUFF OMG

void initRight(fov direction[FOVROWS][FOVCOLS]);

void initLeft(fov dir[FOVROWS][FOVCOLS]);

void initUp(fov dir[FOVROWS][FOVCOLS]);

void initDown(fov dir[FOVROWS][FOVCOLS]);

void initRightUp(fov dir[FOVROWS][FOVCOLS]);

void initRightDown(fov dir[FOVROWS][FOVCOLS]);

void initLeftUp(fov dir[FOVROWS][FOVCOLS]);

void initLeftDown(fov dir[FOVROWS][FOVCOLS]);

//SET CURRENT FOV

void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS]);

void setCurrentFov(mob playr, fov toBecomeCurrentFov[FOVROWS][FOVCOLS], fov r[FOVROWS][FOVCOLS], fov l[FOVROWS][FOVCOLS], fov u[FOVROWS][FOVCOLS], fov d[FOVROWS][FOVCOLS], fov ru[FOVROWS][FOVCOLS], fov rd[FOVROWS][FOVCOLS], fov lu[FOVROWS][FOVCOLS], fov ld[FOVROWS][FOVCOLS]);

// GET PLAYER POS IN CURRENT FOV

mob getPlayerPosInFov(mob playr, mob fovPlayr);

//GET FELTÉTEL FOR FOV TO DISPLAY THE ENTRIE FOV JEEEE

void addFovInfoToMap(map world[WORLDROWS][WORLDCOLS], mob playr, mob fovPlayr, fov fov[FOVROWS][FOVCOLS]);
