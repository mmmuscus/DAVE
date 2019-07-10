#include "animation.h"

animation initNewAnimation(animation anim, string fileName)
{
	fstream fbe (fileName.c_str());
	
	fbe>>anim.frames>>anim.height>>anim.width;
	
	for (int g = 0; g < anim.frames; g++)
	{
		for (int i = 0; i < anim.height; i++)
		{
			for (int j = 0; j < anim.width; j++)
			{
				fbe>>anim.frameArray[g][i][j];
			}
		}
	}

	fbe.close();

	return anim;
}

void animationPlayer(animation anim, int yRow, int xCol)
{
	goTo(yRow, xCol);
}
