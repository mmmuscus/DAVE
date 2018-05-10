#include "actualShadowFunctions.h"

// X COL    Y ROW OMG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// GET COORDINATES OF THE THINGS I GUESS

koordinate getPov(koordinate pov, mob playr, double heigt, double widt)      //DUBLE CHECK NEEDED JUST IN CASE //&&&
{
	if (playr.right && !playr.up && !playr.down)
	{
		pov.x = (playr.col * widt) + widt;
		pov.y = (playr.row * heigt) + (heigt / 2);
	}
	
	if (playr.right && playr.up)
	{
		pov.x = (playr.col * widt) + widt;
		pov.y = (playr.row * heigt);
	}
	
	if (playr.right && playr.down)
	{
		pov.x = (playr.col * widt) + widt;
		pov.y = (playr.row * heigt) + heigt;
	}
	
	if (playr.left && !playr.up && !playr.down)
	{
		pov.x = (playr.col * widt);
		pov.y = (playr.row * heigt) + (heigt / 2);
	}
	
	if (playr.left && playr.up)
	{
		pov.x = (playr.col * widt);
		pov.y = (playr.row * heigt);
	}
	
	if (playr.left && playr.down)
	{
		pov.x = (playr.col * widt);
		pov.y = (playr.row * heigt) + heigt;
	}
	
	if (playr.up && !playr.right && !playr.left)
	{
		pov.x = (playr.col * widt) + (widt / 2);
		pov.y = (playr.row * heigt);
	}
	
	if (playr.down && !playr.right && !playr.left)
	{
		pov.x = (playr.col * widt) + (widt / 2);
		pov.y = (playr.row * heigt) + heigt;
	}
	
	return pov;
}

line getLineEquation(line e, double aXCol, double aYRow, double bXCol, double bYRow)                          //ill give this fgvny the coords amiket megszoroztam a height (2.16) �s a width (1.4375) el 
{
	e.mSlope = (bYRow - aYRow) / (bXCol - aXCol);
	e.bIntercept = aYRow - (e.mSlope * aXCol);
	
	return e;
}

//ezt lehetne szebben is...de van el�g er�s a kompj�ter sz�val...who gives a shit?! xD

//WARNING THIS TWO FOLLOWING FUNCTIONS ARE PROBABLY FUCKED SO WATCH OUT FUTURE SELF IM CAOMING FOR U --PAST SELF P.S.: I HOPE I CAN LOVE U 

//alkalmazni k�ne az ispointover meg ispointunder f�ggv�nyeket

line getLowerLine(line e, koordinate pov, int solidCol, int solidRow, double heigt, double widt)        // tal�n csak az als� kett�t kell csekkolni mert a t�bbi nem lehet als� hat�r???? s akkor vica versa fels� hat�rra
{
	solidCol = solidCol * widt;                                                                         //lehet h ilyet nem szabad csin�lni! :O idk tho! :OOOOOOOOOOOOooo
	solidRow = solidRow * heigt;
	
	e = getLineEquation(e, solidCol + widt, solidRow + heigt, pov.x, pov.y);
	
	if ((solidRow + heigt) > (e.mSlope * solidCol) + e.bIntercept) //this means felette van asszem     //lehet h mivel fejjel lefel� van a koordin�ta rendszer pont rossz rel�ci�jelet haszn�lok
	{
		return e;
	}
	else
	{
		e = getLineEquation(e, solidCol, solidRow + heigt, pov.x, pov.y);
		
		return e;
	}
}

line getUpperLine(line e, koordinate pov, int solidCol, int solidRow, double heigt, double widt)        //alkalmazni k�ne az ispointover meg ispointunder f�ggv�nyeket
{
	solidCol = solidCol * widt;                                                                         //lehet h ilyet nem szabad csin�lni! :O idk tho! :OOOOOOOOOOOOooo
	solidRow = solidRow * heigt;
	
	e = getLineEquation(e, solidCol, solidRow, pov.x, pov.y);
	
	if (solidRow < (e.mSlope * (solidCol + widt)) + e.bIntercept)
	{
		return e;
	}
	else
	{
		e = getLineEquation(e, solidCol + widt, solidRow, pov.x, pov.y);
		
		return e;
	}
}

bool isPointOver(line e, double row, double col)
{
	if (row >= (e.mSlope * col) + e.bIntercept)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isPointUnder(line e, double row, double col)
{
	if (row <= (e.mSlope * col) + e.bIntercept)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isWhollyInShadow(line overLine, line underLine, int row, int col, double heigt, double widt)
{
	col = col * widt;
	row = row * heigt;
	
	if(isPointUnder(overLine, row, col) && isPointOver(underLine, row, col) && isPointUnder(overLine, row + heigt, col) && isPointOver(underLine, row + heigt, col) && isPointUnder(overLine, row, col + widt) && isPointOver(underLine, row, col + widt) && isPointUnder(overLine, row + heigt, col + widt) && isPointOver(underLine, row + heigt, col + widt))
	{
		return true;
	}
	else
	{
		return false;
	}
	
	return true;
}

//bool isBlockedFromLight(line e, bool inShadow, koordinate pov, int row, int col, double heigt, double widt)              //itt az egyenes a  falak s�kj�ban h�zott egyenes, lehet h k�l�n kell egy fgv�nyt csin�lni a f�gg�leges egyenesekre :o
//{
//	if (inShadow)
//	{
//		col = col * widt;
//		row = row * heigt;
//		
//		if (isPointUnder(e, pov.y, pov.x))
//		{
//			if (isPointOver(e, row, col))
//			{
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		else
//		{
//			if (isPointUnder(e, row, col))
//			{
//				return true;
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//}
