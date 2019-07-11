#include "animation.h"

animation initNewAnimation(animation anim, string fileName)
{
	char cahr;
	
	fstream fbe (fileName.c_str());
	
	fbe>>anim.frames>>anim.height>>anim.width;
	
	for (int g = 0; g < anim.frames; g++)
	{
		for (int i = 0; i < anim.height; i++)
		{
			for (int j = 0; j < anim.width; j++)
			{
				fbe>>cahr;
				
				if (cahr == 'i')
				{
					anim.frameArray[g][i][j] = ' ';
				}
				else
				{
					anim.frameArray[g][i][j] = cahr;
				}
			}
		}
	}

	fbe.close();

	return anim;
}

//redo this so it renders onto screenArray and Menuarray
//get an onFrame variable into aniation structure so this all can run more smoothly
void playAnimation(char console[CONSOLEROWS][CONSOLECOLS], animation anim, int currentFrame, int yRow, int xCol)
{
	if (currentFrame < anim.frames)
	{
		for (int i = 0; i < anim.height; i++)
		{
//			goTo(yRow + i, xCol);
//			
			for (int j = 0; j < anim.width; j++)
			{
//				cout<<anim.frameArray[currentFrame][i][j];
				console[yRow + i][xCol + j] = anim.frameArray[currentFrame][i][j];
			}
		}
	}
}
