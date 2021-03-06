#include "shadowFunctions.h"

//SET CURRENT FOV

void makeCurrentFov(fov presetDir[FOVROWS][FOVCOLS], fov toBeDir[FOVROWS][FOVCOLS])
{
	for (int i = 0; i < FOVROWS; i++)
	{
		for (int j = 0; j < FOVCOLS; j++)
		{
			toBeDir[i][j].inView = presetDir[i][j].inView;
//			toBeDir[i][j].isEdge = presetDir[i][j].isEdge;
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

//GET FELT�TEL FOR FOV TO DISPLAY THE ENTRIE FOV JEEEE

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

// X COL    Y ROW OMG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// GET COORDINATES OF THE THINGS I GUESS

koordinate getPov(koordinate pov, mob playr)      //DUBLE CHECK NEEDED JUST IN CASE //&&&
{
	pov.x = playr.col + 0.5;
	pov.y = playr.row + 0.5;

	return pov;
}

//        XCOL               YROW

line getLineEquation(double aXCol, double aYRow, int bXCol, int bYRow)            //(m * xcol) + b
{
	line e;

	e.mSlope = (bYRow - aYRow) / (bXCol - aXCol);
	e.bIntercept = aYRow - (e.mSlope * aXCol);

	return e;
}

bool isUnderLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow <= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow <= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) <= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{   //this shit checks if the point is wholly under the line
		return true;
	}

	return false;
}

bool isOverLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow >= (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow >= ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) >= ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{   //this shit checks if the point is wholly over the line
		return true;
	}

	return false;
}

bool isBetweenLines(line a, line b, int yRow, int xCol)
{
	if (a.isItUnderLine)
	{
		if (!isUnderLine(a, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		if (!isOverLine(a, yRow, xCol))
		{
			return false;
		}
	}

	if (b.isItUnderLine)
	{
		if (!isUnderLine(b, yRow, xCol))
		{
			return false;
		}
	}
	else
	{
		if (!isOverLine(b, yRow, xCol))
		{
			return false;
		}
	}

	return true;
	
	//yes but
}

// just compare the middle points (w correct infinitecimal additions or subtractions) you absolutle cunt lemming
bool isMoreThanHalfInShade(line e, int yRow, int xCol)            //THE PROBLEM IS THE BEHINDWALL AND THIS FUNCTION INTERACTING
{
//	half of the area
//	checked its cool
	//the other case clompletely identical to this one 
	//fractions that dont do numbers
	if (e.isItUnderLine)
	{
		if (xCol - INFINITECIMAL < ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1  > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
//			
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1  > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow + INFINITECIMAL >= 1)
			{
				return true;
			}
		}
//		
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)  //ha a fels� nagyobb mint az als�
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)
				{
					return true;
				}
			}
//			
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)     //kisebb egel m�kszik and w the other felt�tel
				{
					return true;
				}
			}
		}
	}
	
	if (!e.isItUnderLine)
	{
		if (xCol - INFINITECIMAL < (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > (yRow - e.bIntercept) / e.mSlope)
		{
			if (yRow < (e.mSlope * xCol) + e.bIntercept && yRow + 1 > (e.mSlope * xCol) + e.bIntercept)
			{
				return true;
			}
////			
			if (yRow < (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 > (e.mSlope * (xCol + 1)) + e.bIntercept)
			{
				return true;
			}
		}
		
		if (yRow - INFINITECIMAL <= (e.mSlope * xCol) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * xCol) + e.bIntercept && yRow - INFINITECIMAL <= (e.mSlope * (xCol + 1)) + e.bIntercept && yRow + 1 + INFINITECIMAL >= (e.mSlope * (xCol + 1)) + e.bIntercept)
		{
			if ((e.mSlope * xCol) + e.bIntercept - yRow + (e.mSlope * (xCol + 1)) + e.bIntercept - yRow - INFINITECIMAL <= 1)
			{
				return true;
			}
		}
//		
		if (xCol - INFINITECIMAL <= (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= (yRow - e.bIntercept) / e.mSlope && xCol - INFINITECIMAL <= ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL >= ((yRow + 1) - e.bIntercept) / e.mSlope)
		{
			if (((yRow - e.bIntercept) / e.mSlope) - xCol > (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)  //ha a fels� nagyobb mint az als�
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol - INFINITECIMAL <= 1)
				{
					return true;
				}
			}
			
			if (((yRow - e.bIntercept) / e.mSlope) - xCol < (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol)
			{
				if (((yRow - e.bIntercept) / e.mSlope) - xCol + (((yRow + 1) - e.bIntercept) / e.mSlope) - xCol + INFINITECIMAL >= 1)     //kisebb egel m�kszik and w the other felt�tel
				{
					return true;
				}
			}
		}
	}

	return false;

//	if (e.isItUnderLine)
//	{
//		if ((yRow + 0.5) >= ((xCol + 0.5) * e.mSlope) + e.bIntercept)  //ha a line felett van
//		{
//			return true;
//		}
//	}
//	else
//	{
//		if ((yRow + 0.5) <= ((xCol + 0.5) * e.mSlope) + e.bIntercept) //ha alatta
//		{
//			return true;
//		}
//	}

	return false;
	
//	egy m�k�d� dolog
//	if (yRow - INFINITECIMAL < (e.mSlope * xCol) + e.bIntercept && (yRow + 1) + INFINITECIMAL > (e.mSlope * xCol) + e.bIntercept)
//	{
//		return true;
//	}
//	
//	if (yRow - INFINITECIMAL < (e.mSlope * (xCol + 1)) + e.bIntercept && (yRow + 1) + INFINITECIMAL > (e.mSlope * (xCol + 1)) + e.bIntercept)
//	{
//		return true;
//	}
//	
//	if (xCol - INFINITECIMAL < (yRow - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > (yRow - e.bIntercept) / e.mSlope)
//	{
//		return true;
//	}
//	
//	if (xCol - INFINITECIMAL < ((yRow + 1) - e.bIntercept) / e.mSlope && (xCol + 1) + INFINITECIMAL > ((yRow + 1) - e.bIntercept) / e.mSlope)
//	{
//		return true;
//	}
//	
//	return false;
}

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{	
	//16 esetsz�tv�laszt�s	
	//when above or beisde it but its 1 wide/tall
	if (bottom - top == 1 && right - left != 1 && pov.y == top + 0.5)
	{
		if (pov.x < left)
		{
			if (xCol > left)
			{
				return true;
			}
			
			if (xCol >= left && yRow != top)
			{
				return true;
			}
		}
		
		if (pov.x > right)
		{
			if (xCol < right - 1)
			{
				return true;
			}
			
			if (xCol <= right - 1 && yRow != top)
			{
				return true;
			}
		}
	}
	
	if (right - left == 1 && bottom - top != 1 && pov.x == left + 0.5)
	{
		if (pov.y < top)
		{
			if (yRow > top)
			{
				return true;
			}
			
			if (yRow >= top && xCol != left)
			{
				return true;
			}
		}
		
		if (pov.y > bottom)
		{
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			if (yRow <= bottom - 1 && xCol != left)
			{
				return true;
			}
		}
	}
	
	//when above or beside it but its not 1 tall or 1 wide
	if (pov.y > top && pov.y < bottom && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left)
			{
				return true;
			}
			
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1)
			{
				return true;
			}
			
			if (xCol == left && (yRow < top || yRow > bottom - 1))
			{
				return true;
			}
		}
	}
	
	if (pov.x > left && pov.x < right && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > top)
			{
				return true;
			}
			
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < bottom - 1)
			{
				return true;
			}
			
			if (yRow == top && (xCol < left || xCol > right - 1))
			{
				return true;
			}
		}
	}
	
	//when neither above nor beside it
	if (pov.y < top && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left && yRow >= top)
			{
				return true;
			}
			
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1 && yRow >= top)
			{
				return true;
			}
			
			if (xCol == left && yRow > bottom - 1)
			{
				return true;
			}
		}
	}
	
	if (pov.y > bottom - 1 && bottom - top != 1)
	{
		if (pov.x < left)
		{
			if (xCol > left && yRow <= bottom - 1)
			{
				return true;
			}
			
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
		
		if (pov.x > right - 1)
		{
			if (xCol < right - 1 && yRow <= bottom - 1)
			{
				return true;
			}
			
			if (xCol == left && yRow < top)
			{
				return true;
			}
		}
	}
	
	if (pov.x < left && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > top && xCol >= left)
			{
				return true;
			}
			
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < bottom - 1 && xCol >= left)
			{
				return true;
			}
			
			if (yRow == top && xCol > right - 1)
			{
				return true;
			}
		}
	}
	
	if (pov.x > right - 1 && right - left != 1)
	{
		if (pov.y < top)
		{
			if (yRow > bottom - 1 && xCol <= right - 1)
			{
				return true;
			}
			
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
		
		if (pov.y > bottom - 1)
		{
			if (yRow < top && xCol <= right - 1)
			{
				return true;
			}
			
			if (yRow == top && xCol < left)
			{
				return true;
			}
		}
	}
	
	//when 1 by 1
	if (bottom - top == 1 && right - left == 1)
	{
		if (pov.x < left && xCol < left)
		{
			return false;
		}
		
		if (pov.x > right && xCol > right - 1)
		{
			return false;
		}
		
		if (pov.y < top && yRow < top)
		{
			return false;
		}
		
		if (pov.y > bottom && yRow > bottom - 1)
		{
			return false;
		}
		
		if (xCol == left && yRow == top)
		{
			return false;
		}
		
		return true;
	}
	
	return false;
}

// its like the k + 1 thingy but for the whole row/column
//softbehindwalls
bool tShapeDetector(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{
	if (bottom - top == 1)
	{
		if (pov.x < left)
		{
			if (xCol == left)
			{
				return true;
			}
		}
		
		if (pov.x > right)
		{
			if (xCol == right - 1)
			{
				return true;
			}
		}
	}
	
	if (right - left == 1)
	{
		if (pov.y < top)
		{
			if (yRow == top)
			{
				return true;
			}
		}
		
		if (pov.y > bottom)
		{
			if (xCol == bottom - 1)
			{
				return true;
			}
		}
	}
	
	return false;
}

edgeLines getEdgeLines(koordinate pov, int top, int bot, int right, int left)
{
	edgeLines edg;
	
	if (pov.y < top)
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, top);
			edg.second.isItUnderLine = false;
			return edg;
		}
	}
	else if (pov.y > bot)
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else
		{
			edg.first = getLineEquation(pov.x, pov.y, right, bot);
			edg.first.isItUnderLine = true;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
	}
	else
	{
		if (pov.x < left)
		{
			edg.first = getLineEquation(pov.x, pov.y, left, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, left, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
		else if (pov.x > right)
		{
			edg.first = getLineEquation(pov.x, pov.y, right, top);
			edg.first.isItUnderLine = false;
			edg.second = getLineEquation(pov.x, pov.y, right, bot);
			edg.second.isItUnderLine = true;
			return edg;
		}
	}
}

//SHADOW FUNCTIONS
//&&& ha egy v�zszintes t�glalapt�l jobbra van a j�t�kos �s 2 t�vols�gra akkor valami�rt a fels� vonal egyel kor�bban indul(?)
// ^ valahol van egy >= vagy <= egy > vagy egy < helyett i dont care enough to solve it now though...

void shadowFunction(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow, koordinate pov, edgeLines edg)
{
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		int j = 0;
			
		while (j < SCREENCOLS)
		{
			if (world[i + cameraRow][j + cameraCol].solid)
			{
				int k = 0;
				
				while (world[i + cameraRow][j + cameraCol + k].solid)
				{
					k++;
				}
				
				if (k > 1)
				{
					edg = getEdgeLines(pov, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol);
				
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for(int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
							{
								// maybe a second pass is enough with just isBetweenLines
								// possible solution:
								// 1) pass with doesLineIntersect but it wont shade stuff that is solid
								// 2) layer isBetweenLines on top of that
								// 3) patch up function finds "walls" that are surrounded totally with shaded parts and knocks them the fuck out man
								// problem w above solution is that it can be hard to determine such walls, maybe walls that are surrounded by only other walls and shaded areas(?)
								// we need a wariable in the struct that indicates if the square was shaded by the doesLineIntersectIt function, then we "patch" up the thang w the above premise PLUS if that variable is true (and then we reset it)
								// maybe we add a value to the map struct that indicates squares if the solid was NOT shaded by an intersecting line
								// well still need a function that will patch up holes in the ramined of things, perb the function that gives the green light to the shading function could do that too
								//		when the thingy is surrounded on all sides by walls and/or shaded cells then its shaded, if not then we check if it was shaded by doesLineINtersectIT
								
								// perb we need to compute all shaded areas and then go through the array o vbisible cells w a fnction that determines if at least .5 of the cell is shaded
								// problem w this is all the angles and overlaps the lines could take
								
								// add sub variable to map structure .shadedThisPass set this to true if you shaded w this wall in this pass then go for walls w 1xk dimensions where k > 1 and do the doesLineIntersect then shade the 1x1 ones
								//		maybe add another sub variable .wasThis1Long and you set this to true in the first pass eery time k was 1 then shade the ones that have this as true and k is 1 for them in the second pass 
								//		ofc reset both of these sub variables every frame
								
								
								// Problem statement(s):
								// a) if we just put isbetweenlines and does it intesect to work then some walls will shade themselves
								// b) if we put the above two functions to work with the twist of if this wall has walls in of the opposite orientation as itself at correct end they dnt get shaded, then 'T' shaped "intersections" can still
								//    shade the wrong walls
								// c) if we go isbetweenlines -> doesitintersect and dont let the latter function shade solids then the solids that SHOULD be shaded by this function arent, and we cant dercide easily which are these solids
								// d) if we add a subvariable to the structure that determines if the wall was shaded with already the problem here is that if we shade an intersecting wall in a 'T' shape b4 we shade the other it fucks up
								
								// Dem solutions tho
								// a) some form of complex wall detection (citation needed)
								// b) an interpretor that determines which walls are closer to the player (citation needed)
								// c) samey problem as above and therfore possible solution (citation needed)
								//    
								// d) samey problem as b) therefore samey solution (citation needed)
								
								// add a soft isBehindWall where if its a wall and doesItIntersect is ture then we make it in view and also apply the c) solution w this
								
								
								// this below is bs
								// we make sure we only shade w vsible bits of wall and then after we shaded w em we set their visibility back to true   (???)
								
								// only that one sucks which has the 'T' shape upside down  
								
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									//here should the variable in the structure change
									
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
								{
//									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
//									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
//									}
								}
								
								// && if player at one side and the t shape is not a solid
//								if (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))
//								{
									//commenting this out makes it behave correctly xcept for the problem we wanna solve so tweak this and run th regular tests
									//due to the other half malfunctioning its only showing 6 'x's but in reality theres 8 so the shadings good the display is the only sucky thang
									//when up against a not one long side of a wall and at the end of the wall the 1 sloped line does not function as it should
									//when uo against the 1 long side of a wall the 1 sloped line computes correctly when looking left to right
									
									//maybe usual test is not good cos that should be taken care of in the other pass of the shading....man wtf
//									if (pov.x < j + cameraCol)
//									{
//										if ((g == i - 1 && h == j && !world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j && !world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = false;
//										}
//									}
//									else
									//if commenting this out the up against the 1 long wall 1 slope shading is solved when looking from right to left
//									if (pov.x > j + k + cameraCol - 1)
//									{
//										if ((g == i - 1 && h == j + k - 1 && !world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j + k - 1 && !world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = false;
//										}
//									}
//									else
//									{
//										world[g + cameraRow][h + cameraCol].mapInView = false;
//									}

		//shit above is tha algorythm

//									if (pov.x < j + cameraCol)
//									{
//										if ((g == i - 1 && h == j && world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j && world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = true;
//										}
//									}
//								
//									if (pov.x > j + k + cameraCol - 1)
//									{
//										if ((g == i - 1 && h == j + k - 1 && world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j + k - 1 && world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = true;
//										}
//									}
//								}
								
//								if (pov.x < j + cameraCol)
//								{
//									if ((g == i - 1 && h == j && world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j && world[g + cameraRow][h + cameraCol].solid))
//									{
//										world[g + cameraRow][h + cameraCol].mapInView = true;
//									}
//								}
//								
//								if (pov.x > j + k + cameraCol - 1)
//								{
//									if ((g == i - 1 && h == j + k - 1 && world[g + cameraRow][h + cameraCol].solid) || (g == i + 1 && h == j + k - 1 && world[g + cameraRow][h + cameraCol].solid))
//									{
//										world[g + cameraRow][h + cameraCol].mapInView = true;
//									}
//								}
							}
						}
					}
					
//					for (int g = 0; g < SCREENROWS; g++)
//					{
//						for (int h = 0; h < SCREENROWS; h++)
//						{
//							//yeye stuffz
//						}
//					}
				}
//				else if (!world[j + cameraRow + 1][i + cameraCol].solid && !world[j + cameraRow - 1][i + cameraCol].solid)
//				{
//					edg = getEdgeLines(pov, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol);
//					
//					for (int g = 0; g < SCREENROWS; g++)
//					{
//						for (int h = 0; h < SCREENCOLS; h++)
//						{
//							if (isBehindWall(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
//							{
//								if (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))
//								{
//									world[g + cameraRow][h + cameraCol].mapInView = false;
//								}
//								
//								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
//								{
//									world[g + cameraRow][h + cameraCol].mapInView = false;
//								}
//							}
//						}
//					}
//				}
				
				j += k;
			}
			else
			{
				j++;
			}
		}
	}
	
	for (int i = 0; i < SCREENCOLS; i++)
	{
		int j = 0;
		
		while (j < CONSOLEROWS)
		{
			if (world[j + cameraRow][i + cameraCol].solid)
			{
				int k = 0;
				
				while (world[j + cameraRow + k][i + cameraCol].solid)
				{
					k++;
				}
//				
				if (k > 1)
				{
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
				
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									//here should the variable in the structure change
									
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
								{
//									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
//									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
//									}
								}
								
//								if (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))
//								{
//									if (pov.y < j + cameraRow)
//									{
//										if ((h == i - 1 && g == j && !world[g + cameraRow][h + cameraCol].solid) || (h == i + 1 && g == j && !world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = false;
//										}
//									}
//									
//									if (pov.y > j + k + cameraRow - 1)
//									{
//										if ((h == i - 1 && g == j + k - 1 && !world[g + cameraRow][h + cameraCol].solid) || (h == i + 1 && g == j + k - 1 && !world[g + cameraRow][h + cameraCol].solid))
//										{
//											world[g + cameraRow][h + cameraCol].mapInView = false;
//										}
//									}
////									
//									if (pov.y >= j + cameraCol && pov.y <= j + k + cameraCol - 1)
//									{
//										world[g + cameraRow][h + cameraCol].mapInView = false;
//									}
//								}
							}
						}
					}
					
//					for (int g = 0; g < SCREENROWS; g++)
//					{
//						for (int h = 0; h < SCREENROWS; h++)
//						{
//							//yeye stuffz
//						}
//					}
				}
				else if (!world[j + cameraRow][i + cameraCol + 1].solid && !world[j + cameraRow][i + cameraCol - 1].solid)
				{
					edg = getEdgeLines(pov, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol);
					
					for (int g = 0; g < CONSOLEROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isBehindWall(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
							{
								if (isMoreThanHalfInShade(edg.first, g + cameraRow, h + cameraCol) || isMoreThanHalfInShade(edg.second, g + cameraRow, h + cameraCol))
								{
									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, j + cameraRow, j + k + cameraRow, i + cameraCol + 1, i + cameraCol))
									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
									}
								}
								
								if (isBetweenLines(edg.first, edg.second, g + cameraRow, h + cameraCol)/* || (doesLineIntersectIt(edg.first, g + cameraRow, h + cameraCol) || doesLineIntersectIt(edg.second, g + cameraRow, h + cameraCol))*/)
								{
//									if (!world[g + cameraRow][h + cameraCol].solid || !tShapeDetector(pov, g + cameraRow, h + cameraCol, i + cameraRow, i + cameraRow + 1, j + k + cameraCol, j + cameraCol))
//									{
										world[g + cameraRow][h + cameraCol].mapInView = false;
//									}
								}
							}
						}
					}
				}
				
				j += k;  //lol jk xD
			}
			else
			{
				j++;
			}
		}
	}
	
//	world[pov.y - 0.5][pov.x - 0.5].mapInView = true;
}

void holePlugger(map world[WORLDROWS][WORLDCOLS], int cameraCol, int cameraRow)
{
	for (int i = 0; i < SCREENCOLS; i++)
	{
		for (int j = 0; j < CONSOLEROWS; j++)
		{
			if (world[j + cameraRow][i + cameraCol].mapInView)
			{
				if ((world[j + cameraRow + 1][i + cameraCol].solid || !world[j + cameraRow + 1][i + cameraCol].mapInView) && (world[j + cameraRow - 1][i + cameraCol].solid || !world[j + cameraRow - 1][i + cameraCol].mapInView) && (world[j + cameraRow][i + cameraCol + 1].solid || !world[j + cameraRow][i + cameraCol + 1].mapInView) && (world[j + cameraRow][i + cameraCol - 1].solid || !world[j + cameraRow][i + cameraCol - 1].mapInView))
				{
					world[j + cameraRow][i + cameraCol].mapInView = false;
				}
			} 
		}
	}
}

// i need to rewrite this cos sg is really bad
// there is still a bug it is shaped like the camera, while there is a camera pan
bool isBesideNotSolidInView(map world[WORLDROWS][WORLDCOLS], int xCol, int yRow)
{
	for (int i = yRow - 1; i <= yRow + 1; i++)
	{
		for (int j = xCol - 1; j <= xCol + 1; j++)
		{
			if (world[j][i].mapInView/* && !world[j][i].solid*/)
			{
				return true;
			}
		}
	}
	
	return false;
}

void mapIsEdgeCalculation(map world[WORLDROWS][WORLDCOLS], int cameraRow, int cameraCol)
{
	//possible bugfix
	//looping through the rows and cols just outside view, and making them not in view so the rows and cols beside wont register falsly as isEdge
	for (int i = 0; i < CONSOLEROWS + 2; i++)
	{
		world[cameraRow - 1 + i][cameraCol - 1].mapInView = false;
		world[cameraRow - 1 + i][cameraCol + SCREENCOLS].mapInView = false;
	}
	
	for (int i = 0; i < SCREENCOLS + 2; i++)
	{
		world[cameraRow - 1][cameraCol - 1 + i].mapInView = false;
		world[cameraRow + CONSOLEROWS][cameraCol - 1 + i].mapInView = false;
	}
	
	//re rewrite time:
	for (int i = 0; i < CONSOLEROWS; i++)
	{
		for (int j = 0; j < SCREENCOLS; j++)
		{
			if (!world[i + cameraRow][j + cameraCol].mapInView)
			{
//				function which decides if there are any spaces beside this one that are in view and not solid
				if (isBesideNotSolidInView(world, i + cameraRow, j + cameraCol))
				{
					world[i + cameraRow][j + cameraCol].mapIsEdge = true;
				}
			}
		}
	}
}
