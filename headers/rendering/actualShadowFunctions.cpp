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

line getLineEquation(int aXCol, int aYRow, int bXCol, int bYRow)            //(m * xcol) + b
{
	line e;

	e.mSlope = (double)(bYRow - aYRow) / (bXCol - aXCol);
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
	if ((solidYRow < (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) < (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow < ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) < ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{   //this shit checks if the point is wholly under the line
		return true;
	}

	return false;
}

bool isOverLine(line e, int solidYRow, int solidXCol)
{
	if ((solidYRow > (solidXCol * e.mSlope) + e.bIntercept) && ((solidYRow + 1) > (solidXCol * e.mSlope) + e.bIntercept) && (solidYRow > ((solidXCol + 1) * e.mSlope) + e.bIntercept) && ((solidYRow + 1) > ((solidXCol + 1) * e.mSlope) + e.bIntercept))
	{   //this shit checks if the point is wholly over the line
		return true;
	}

	return false;
}

bool isWhollyInShadow (line a, line b, bool upperA, bool upperB, int yRow, int xCol)
{
	if (upperA)
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

	if (upperB)
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

bool isBehindWall(koordinate pov, int yRow, int xCol, bool nextTo, bool underOver, int top, int bottom, int right, int left)
{
	if (nextTo)      //ill foglalkoz with this shit when ill do the other irányú végigmenés on the screen
	{
		if ((pov.x < left) && (xCol >= right))
		{
			return true;
		}

		if ((pov.x >= right) && (xCol < left))
		{
			return true;
		}

		return false;
	}

	if (underOver)
	{
		if ((pov.y < top) && (yRow >= bottom))
		{
			return true;
		}

		if ((pov.y >= bottom) && (yRow < top))
		{
			return true;
		}
	}

	if (((pov.x < left) && (xCol >= right)) || ((pov.y < top) && (yRow >= bottom)))
	{
		return true;
	}

	if (((pov.x < left) && (xCol >= right)) || ((pov.y >= bottom) && (yRow < top)))
	{
		return true;
	}

	if (((pov.x >= right) && (xCol < left)) || ((pov.y < top) && (yRow >= bottom)))
	{
		return true;
	}

	if (((pov.x >= right) && (xCol < left)) || ((pov.y >= bottom) && (yRow < top)))
	{
		return true;
	}

	return false;
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

    bool found = false;

    koordinate teglalap[2][2];

    teglalap[0][1].x = right;  //top right
    teglalap[0][1].y = top;

    teglalap[0][0].x = left;   //top left
    teglalap[0][0].y = top;

    teglalap[1][1].x = right;  //bottom right
    teglalap[1][1].y = bottom;

    teglalap[1][0].x = left;   //bottom left
    teglalap[1][0].y = bottom;

    int i = 0;
    int j = 0;

    int pointPosCounter = 0;
    
    //so far so good
    //where do i ++ i or j?!?!?!?!

    while(!found && i <= 1 && j <= 1)
    {
        e = getLineEquation(pov.x, pov.y, teglalap[i][j].x, teglalap[i][j].y);

        pointPosCounter = 0;

        for (int g = 0; g <= 1; g++)
        {
            for (int h = 0; h <= 1; h++)
            {
                if (teglalap[g][h].y > (teglalap[g][h].x * e.mSlope) + e.bIntercept)
                {
                    pointPosCounter++;
                }
                else
                {
                    pointPosCounter--;
                }
            }
        }

        if (!doesFirstLineExist)
        {
            if (pointPosCounter == 3 || pointPosCounter == -3)
            {
                found = true;
                return e;
            }
        }
        else
        {
            if ((e.mSlope != firstLine.mSlope || e.bIntercept != firstLine.bIntercept) && (pointPosCounter == 3 || pointPosCounter == -3))
            {
                found = true;
                return e;
            }
        }
    }
}
