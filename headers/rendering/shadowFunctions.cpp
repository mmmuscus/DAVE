#include "shadowFunctions.h"

using namespace std;

//INITIALISE THE STUFF OMG

void initRight(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/right.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initLeft(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/left.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initUp(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/up.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initDown(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/down.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initRightUp(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/rightUp.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initRightDown(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/rightDown.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initLeftUp(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/leftUp.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

void initLeftDown(fov dir[FOVROWS][FOVCOLS])
{
	char cahr;
	
	fstream fbe ("FOVs/leftDown.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			fbe>>cahr;
			
			if (cahr == 'x' || cahr == '_')
			{
				dir[i][j].inView = true;
				
				if (cahr == '_')
				{
					dir[i][j].isEdge = true;
				}
				else
				{
					dir[i][j].isEdge = false;
				}
			}
			else
			{
				dir[i][j].inView = false;
				dir[i][j].isEdge = false;
			}
			
			if (cahr == '@')
			{
				dir[i][j].isPlayer = true;
				dir[i][j].inView = true;
			}
			else
			{
				dir[i][j].isPlayer = false;
			}
		}
	}
	
	fbe.close();
}

//SET CURRENT FOV

void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS])
{
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			toBeDir[i][j].inView = presetDir[i][j].inView;
			toBeDir[i][j].isEdge = presetDir[i][j].isEdge;
			toBeDir[i][j].isPlayer = presetDir[i][j].isPlayer;
		}
	}
}

void setCurrentFov(mob playr, fov toBecomeCurrentFov[FOVROWS][FOVCOLS], fov r[FOVROWS][FOVCOLS], fov l[FOVROWS][FOVCOLS], fov u[FOVROWS][FOVCOLS], fov d[FOVROWS][FOVCOLS], fov ru[FOVROWS][FOVCOLS], fov rd[FOVROWS][FOVCOLS], fov lu[FOVROWS][FOVCOLS], fov ld[FOVROWS][FOVCOLS])
{
	if (playr.right && !playr.up && !playr.down)
	{
		makeCurrentFov(r, toBecomeCurrentFov);
	}
	
	if (playr.right && playr.up)
	{
		makeCurrentFov(ru, toBecomeCurrentFov);
	}
	
	if (playr.right && playr.down)
	{
		makeCurrentFov(rd, toBecomeCurrentFov);
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		makeCurrentFov(l, toBecomeCurrentFov);
	}
	
	if (playr.left && playr.up)
	{
		makeCurrentFov(lu, toBecomeCurrentFov);
	}
	
	if (playr.left && playr.down)
	{
		makeCurrentFov(ld, toBecomeCurrentFov);
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		makeCurrentFov(u, toBecomeCurrentFov);
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		makeCurrentFov(d, toBecomeCurrentFov);
	}
}

// GET PLAYER POS IN CURRENT FOV

mob getPlayerPosInFov(mob playr, mob fovPlayr)
{
	if (playr.right && !playr.up && !playr.down)
	{
		fovPlayr.row = 10;
		fovPlayr.col = 1;
	}
	
	if (playr.right && playr.up)
	{
		fovPlayr.row = 14;
		fovPlayr.col = 7;
	}
	
	if (playr.right && playr.down)
	{
		fovPlayr.row = 6;
		fovPlayr.col = 7;
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		fovPlayr.row = 10;
		fovPlayr.col = 33;
	}
	
	if (playr.left && playr.up)
	{
		fovPlayr.row = 14;
		fovPlayr.col = 27;
	}
	
	if (playr.left && playr.down)
	{
		fovPlayr.row = 6;
		fovPlayr.col = 27;
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		fovPlayr.row = 20;
		fovPlayr.col = 17;
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		fovPlayr.row = 0;
		fovPlayr.col = 17;
	}
	
	return fovPlayr;
}

//GET FELTÉTEL FOR FOV TO DISPLAY THE ENTRIE FOV JEEEE

void addFovInfoToMap(map world[WORLDROWS][WORLDCOLS], mob playr, mob fovPlayr, fov fov[FOVROWS][FOVCOLS])
{
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			world[i][j].mapIsEdge = false;
			world[i][j].mapInView = false;
		}
	}
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			if (fov[i][j].inView)
			{
				world[playr.row - fovPlayr.row + i][playr.col - fovPlayr.col + j].mapInView = true;
				
				if (fov[i][j].isEdge)
				{
					world[playr.row - fovPlayr.row + i][playr.col - fovPlayr.col + j].mapIsEdge = true;
				}
			}
		}
	}
}
