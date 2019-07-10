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

void playAnimation(animation anim, int currentFrame, int yRow, int xCol)
{
	if (currentFrame < anim.frames)
	{
		for (int i = 0; i < anim.height; i++)
		{
			goTo(yRow + i, xCol);
			
			for (int j = 0; j < anim.width; j++)
			{
				cout<<anim.frameArray[currentFrame][i][j];
			}
		}
	}
}
