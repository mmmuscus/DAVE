#include "debug.h"

using namespace std;

void drawTestMap(map world[WORLDROWS][WORLDCOLS])
{
	ofstream fki ("testmap.txt");
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			fki<<world[i][j].texture;
		}
		
		fki<<"\n";
	}
	
	fki.close();
}

void drawTestWalkable(map world[WORLDROWS][WORLDCOLS])
{
	ofstream fki ("testwalk.txt");
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			if (world[i][j].walkable == true)
			{
				fki<<' ';
			}
			else 
			{
				fki<<'f';
			}
		}
		
		fki<<"\n";
	}
	
	fki.close();
}

void drawTestSolid(map world[WORLDROWS][WORLDCOLS])
{
	ofstream fki ("testsolid.txt");
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			if (world[i][j].solid == true)
			{
				fki<<'t';
			}
			else 
			{
				fki<<' ';
			}
		}
		
		fki<<"\n";
	}
	
	fki.close();
}

void drawTestFov(fov dir[FOVROWS][FOVCOLS])
{
	ofstream fki ("testDir.txt");
	
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			if (dir[i][j].inView)
			{
				if (dir[i][j].isEdge)
				{
					fki<<":";
				}
				else
				{
					fki<<"x";
				}
			}
			else
			{
				if (dir[i][j].isPlayer)
				{
					fki<<"@";
				}
				else
				{
					fki<<" ";
				}
			}
		}
		
		fki<<"\n";
	}
	
	fki.close();
}

void drawTestInView(map world[WORLDROWS][WORLDCOLS])
{
	ofstream fki ("testview.txt");
	
	for (int i = 0; i < WORLDROWS; i++)
	{
		for (int j = 0; j < WORLDCOLS; j++)
		{
			if (world[i][j].mapInView == true)
			{
				fki<<'t';
			}
			else 
			{
				fki<<' ';
			}
		}
		
		fki<<"\n";
	}
	
	fki.close();
}
