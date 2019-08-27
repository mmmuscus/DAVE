#include "input.h"

//KEYINPUT

bool wPressed()
{
	return (GetKeyState('W') & 0x8000);
}

bool aPressed()
{
	return (GetKeyState('A') & 0x8000);
}

bool sPressed()
{
	return (GetKeyState('S') & 0x8000);
}

bool dPressed()
{
	return (GetKeyState('D') & 0x8000);
}

bool ePressed()
{
	return (GetKeyState('E') & 0x8000);
}

bool escPressed()
{
	return (GetKeyState(VK_ESCAPE) & 0x8000);
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
