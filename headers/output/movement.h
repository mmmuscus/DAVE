#include "../system/system.h"

mob playerMovement(mob playr, bool w, bool s, bool a, bool d);

mob keepInBounds(mob playr, mob lastPlayr, map world[WORLDROWS][WORLDCOLS]);

mob setDirections(mob playr, bool w, bool s, bool a, bool d);

mob camMovement(mob cam, mob playr);

mob cameraPan(mob cam, mob camDest);                                                                       //&&& SLOWPAN OR FASTPAN????????????

mob keepCamInBounds(mob cam, map world[WORLDROWS][WORLDCOLS]);
