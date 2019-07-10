#include "shadowFunctions.h"

animation initAnimation(animation anim, string fileName)
{
	fstream fbe (fileName.c_str());
//	freopen(fileName.c_str(),"r",stdin);
	
	fbe>>anim.frames>>anim.height>>anim.width;
//	cin>>anim.frames>>anim.height>>anim.width;
	
//	anim.frames = 2;   //116
//	anim.height = 24;
//	anim.width = 39;
	
	for (int g = 0; g < anim.frames; g++)
	{
		for (int i = 0; i < anim.height; i++)
		{
			for (int j = 0; j < anim.width; j++)
			{
				fbe>>anim.frameArray[g][i][j];
//				cin>>anim.frameArray[g][i][j];
			}
		}
	}
	
	fbe.close();
//	fclose(stdin);

	return anim;
}
