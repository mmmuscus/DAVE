#include "actualShadowFunctions.h"

// X COL    Y ROW OMG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// GET COORDINATES OF THE THINGS I GUESS

koordinate getPov(koordinate pov, mob playr, double heigt, double widt)      //DUBLE CHECK NEEDED JUST IN CASE //&&&
{
//	version 1: all of the different player stances have different pov points
//	if (playr.right && !playr.up && !playr.down)
//	{
//		pov.x = (playr.col * widt) + widt;
//		pov.y = (playr.row * heigt) + (heigt / 2);
//	}
//
//	if (playr.right && playr.up)
//	{
//		pov.x = (playr.col * widt) + widt;
//		pov.y = (playr.row * heigt);
//	}
//
//	if (playr.right && playr.down)
//	{
//		pov.x = (playr.col * widt) + widt;
//		pov.y = (playr.row * heigt) + heigt;
//	}
//
//	if (playr.left && !playr.up && !playr.down)
//	{
//		pov.x = (playr.col * widt);
//		pov.y = (playr.row * heigt) + (heigt / 2);
//	}
//
//	if (playr.left && playr.up)
//	{
//		pov.x = (playr.col * widt);
//		pov.y = (playr.row * heigt);
//	}
//
//	if (playr.left && playr.down)
//	{
//		pov.x = (playr.col * widt);
//		pov.y = (playr.row * heigt) + heigt;
//	}
//
//	if (playr.up && !playr.right && !playr.left)
//	{
//		pov.x = (playr.col * widt) + (widt / 2);
//		pov.y = (playr.row * heigt);
//	}
//
//	if (playr.down && !playr.right && !playr.left)
//	{
//		pov.x = (playr.col * widt) + (widt / 2);
//		pov.y = (playr.row * heigt) + heigt;
//	}

//	version2: same pov point for every player stance
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

rectangle getRectangleEdges(koordinate pov, int top, int bottom, int right, int left)
{
	rectangle r;

	if ((pov.x <= left) && (pov.y < top))
	{
		r.a.x = right;
		r.a.y = top;
		r.b.x = left;
		r.b.y = bottom;
	}

	if ((pov.x <= left) && (pov.y >= bottom))
	{
		r.a.x = left;
		r.a.y = top;
		r.b.x = right;
		r.b.y = bottom;
	}

	if ((pov.x > right) && (pov.y < top))
	{
		r.a.x = left;
		r.a.y = top;
		r.b.x = right;
		r.b.y = bottom;
	}

	if ((pov.x > right) && (pov.y >= bottom))
	{
		r.a.x = right;
		r.a.y = top;
		r.b.x = left;
		r.b.y = bottom;
	}

	if ((pov.x <= left) && (pov.y > top) && (pov.y <= bottom))
	{
		r.a.x = left;
		r.a.y = top;
		r.b.x = left;
		r.b.y = top;
	}

	if ((pov.x > right) && (pov.y > top) && (pov.y <= bottom))
	{
		r.a.x = right;
		r.a.y = top;
		r.b.x = right;
		r.b.y = bottom;
	}

	if ((pov.y < top) && (pov.x < right) && (pov.x >= left))
	{
		r.a.x = right;
		r.a.y = top;
		r.b.x = left;
		r.b.y = top;
	}

	if ((pov.y >= bottom) && (pov.x < right) && (pov.x >= left))
	{
		r.a.x = right;
		r.a.y = bottom;
		r.b.x = left;
		r.b.y = bottom;
	}

	return r;
}

bool isLineOverLine(line e, double middleOfFirstSolidYRow, double middleOfFirstSolidXCol)
{
	if(middleOfFirstSolidYRow < (middleOfFirstSolidXCol * e.mSlope) + e.bIntercept)
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool isBetweenLines (line a, line b, int yRow, int xCol)
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
}

bool isPlayerNextToRectangle(koordinate pov, int top, int bottom, int right, int left)
{
	if ((pov.y >= top) && (pov.y <= bottom))
	{
		return true;
	}

	return false;
}

bool isPlayerOverOrUnderRectangle(koordinate pov, int top, int bottom, int right, int left)
{
	if ((pov.x >= left) && (pov.x <= right))
	{
		return true;
	}

	return false;
}

bool isBehindWall(koordinate pov, int yRow, int xCol, int top, int bottom, int right, int left)
{
	if (pov.x < left && xCol < left + 1)
	{
		return false;
	}
	
	if (pov.x > right && xCol > right - 2)      //dunno why i need to do it
	{
		return false;
	}
	
	if (pov.y < top && yRow < top + 1)
	{
		return false;
	}
	
	if (pov.y > bottom && yRow > bottom - 2)    //dunno why i need to do it
	{
		return false;
	}
	
	return true;
}

line makeLineNull(line e)
{
	e.bIntercept = 0;
	e.mSlope = 0;
}

// second megoldas mayb lets see
// u need a bool isUnderline part to the line struct and you can change it from this function (if its +3 its true if its -3 its false)

line getLineOfSight(koordinate pov, int top, int bottom, int right, int left, line firstLine, bool doesFirstLineExist)
{
    line e;

//    koordinate teglalap[4];
//
//    teglalap[0].x = right;  //top right
//    teglalap[0].y = top;
//
//    teglalap[1].x = left;   //top left
//    teglalap[1].y = top;
//    
//    teglalap[2].x = left;   //bottom left
//    teglalap[2].y = bottom;
//
//    teglalap[3].x = right;  //bottom right
//    teglalap[3].y = bottom;
    
    koordinate teglalap[2][2];

    teglalap[0][0].x = right;  //top right
    teglalap[0][0].y = top;

    teglalap[0][1].x = left;   //top left
    teglalap[0][1].y = top;
    
    teglalap[1][0].x = left;   //bottom left
    teglalap[1][0].y = bottom;

    teglalap[1][1].x = right;  //bottom right
    teglalap[1][1].y = bottom;

    int pointPosCounter = 0;
    
    //so far so good
    
    //rewrite time...
//    for (int i = 0; i < 4; i++)
//    {
//    	e = getLineEquation(pov.x, pov.y, teglalap[i].x, teglalap[i].y);
//    	
//    	pointPosCounter = 0;
//    	
//    	for (int j = 0; j < 4; j++)
//    	{
//    		if (teglalap[j].y > (teglalap[j].x * e.mSlope) + e.bIntercept)
//    		{
//    			pointPosCounter++;
//			}
//			else if (teglalap[j].y < (teglalap[j].x * e.mSlope) + e.bIntercept)
//			{
//				pointPosCounter--;
//			}
//		}
//		
//		if (doesFirstLineExist)
//		{
//			if (firstLine.mSlope != e.mSlope || firstLine.bIntercept != e.bIntercept)
//			{
//				if (pointPosCounter == 3)
//				{
//					e.isItUnderLine = true;
//					return e;
//				}
//				else if (pointPosCounter = -3)
//				{
//					e.isItUnderLine = false;
//					return e;
//				}
//			}
//		}
//		else
//		{
//			if (pointPosCounter == 3)
//			{
//				e.isItUnderLine = true;
//				return e;
//			}
//			else if (pointPosCounter = -3)
//			{
//				e.isItUnderLine = false;
//				return e;
//			}
//		}
//	}

    for (int i = 0; i <= 1; i++)
    {
    	for (int j = 0; j <= 1; j++)
    	{
    		e = getLineEquation(pov.x, pov.y, teglalap[i][j].x, teglalap[i][j].y);

        	pointPosCounter = 0;

        	for (int g = 0; g <= 1; g++)
        	{
            	for (int h = 0; h <= 1; h++)
            	{
            	    if (teglalap[g][h].y >= (teglalap[g][h].x * e.mSlope) + e.bIntercept)
                	{
                    	pointPosCounter++;
                	}
                	else if (teglalap[g][h].y <= (teglalap[g][h].x * e.mSlope) + e.bIntercept)
                	{
                	    pointPosCounter--;
                	}
            	}
        	}

        	if (!doesFirstLineExist)
        	{
            	if (pointPosCounter == 4)
            	{
                	e.isItUnderLine = false;
                	return e;
				}
				else if (pointPosCounter == -4)
				{
					e.isItUnderLine = true;
                	return e;
				}
        	}
        	else
        	{
            	if (e.mSlope != firstLine.mSlope && e.bIntercept != firstLine.bIntercept)
            	{
                	if (pointPosCounter == 4)
                	{
                		e.isItUnderLine = false;
                		return e;
					}
					else if (pointPosCounter == -4)
					{
						e.isItUnderLine = true;
                		return e;
					}
            	}
        	}
		}
    }
}

edgeLines getEdges(koordinate pov, int top, int bot, int right, int left)
{
	edgeLines edg;
	
	koordinate rect[4];
	
	rect[0].x = right;
	rect[0].y = top;
	
	rect[1].x = right;
	rect[1].y = bot;
	
	rect[2].x = left;
	rect[2].y = top;
	
	rect[3].x = left;
	rect[3].y = bot;
	
	int pointPosCounter = 0;
	
	int i = 0;
	
	bool isFound = false;
	
	while (!isFound)
	{
		edg.first = getLineEquation(pov.x, pov.x, rect[i].x, rect[i].y);
		
		if (isOverLine(edg.first, top, right))
		{
			edg.first.isItUnderLine = true;
			isFound = true;
		}
		else if (isUnderLine(edg.first, top, right))
		{
			edg.first.isItUnderLine = false;
			isFound = true;
		}
		
		i++;
	}
	
	isFound = false;
	
	while (!isFound)
	{
		edg.second = getLineEquation(pov.x, pov.x, rect[i].x, rect[i].y);
		
		if (isOverLine(edg.second, top, right))
		{
			edg.second.isItUnderLine = true;
			isFound = true;
		}
		else if (isUnderLine(edg.second, top, right))
		{
			edg.second.isItUnderLine = false;
			isFound = true;
		}
		
		i++;
	}
	
	return edg;
}

//xcol yrow

line getFirstLine(koordinate pov, int top, int bot, int right, int left)
{
	line e; 
	
	if (pov.x < left && pov.y < bot)
	{
		e = getLineEquation(pov.x, pov.y, left, bot);
		e.isItUnderLine = true;
		return e;
	}
	
	if (pov.x > left && pov.y < top)
	{
		e = getLineEquation(pov.x, pov.y, left, top);
		e.isItUnderLine = false;
		return e;
	}
	
	if (pov.x > right && pov.y > top)
	{
		e = getLineEquation(pov.x, pov.y, right, top);
		e.isItUnderLine = false;
		return e;
	}
	
	if (pov.x < right && pov.y > bot)
	{
		e = getLineEquation(pov.x, pov.y, right, bot);
		e.isItUnderLine = true;
		return e;
	}
}

line getSecondLine(koordinate pov, int top, int bot, int right, int left)
{
	line e;
	
	if (pov.x < right && pov.y < top)
	{
		e = getLineEquation(pov.x, pov.y, right, top);
		e.isItUnderLine = false;
		return e;
	}
	
	if (pov.x < left && pov.y > top)
	{
		e = getLineEquation(pov.x, pov.y, left, top);
		e.isItUnderLine = false;
		return e;
	}
	
	if (pov.x > left && pov.y > bot)
	{
		e = getLineEquation(pov.x, pov.y, left, bot);
		e.isItUnderLine = true;
		return e;
	}
	
	if (pov.x > right && pov.y < bot)
	{
		e = getLineEquation(pov.x, pov.y, right, bot);
		e.isItUnderLine = true;
		return e;
	}
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

bool isInShadow(line a, line b, int yRow, int xCol, koordinate pov, int top, int bot, int right, int left)
{
	if (isBetweenLines(a, b, yRow, xCol) && isBehindWall(pov, yRow, xCol, top, bot, right, left))
	{
		return true;
	}
	else
	{
		return false;
	}
	
//	if (!isBehindWall(pov, yRow, xCol, top, bot, right, left))
//	{
//		return false;
//	}
	
//	if (bot - top == 1)
//	{
//		if (pov.y == top)
//		{
//			
//		}
//	}
//	else if (right - left == 1)
//	{
//		if (pov.x == left)
//		{
//			
//		}
//	}
}
