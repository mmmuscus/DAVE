#include "input.h"

//KEYINPUT

bool wPressed()
{
	if (GetKeyState('W') & 0x8000)
	{
		return true;
	}
}

bool aPressed()
{
	if (GetKeyState('A') & 0x8000)
	{
		return true;
	}
}

bool sPressed()
{
	if (GetKeyState('S') & 0x8000)
	{
		return true;
	}
}

bool dPressed()
{
	if (GetKeyState('D') & 0x8000)
	{
		return true;
	}
}

bool ePressed()
{
	if (GetKeyState('E') & 0x8000)
	{
		return true;
	}
}

bool escPressed()
{
	if (GetKeyState(VK_ESCAPE) & 0x8000) 
	{
		return true;
	}
}

//in getInput(in in)
//{
//	in.w = false;
//	in.s = false;
//	in.a = false;
//	in.d = false;
//	in.esc = false;
//	
//	in.w = wPressed();
//	in.s = sPressed();
//	in.a = aPressed();
//	in.d = dPressed();
//	in.esc = escPressed();
//	
//	return in;
//}


//INPUT HANDLEING

void cancelOut (bool plus, bool minus)
{
	if (plus && minus)
	{
		plus = false;
		minus = false;
	}
}
