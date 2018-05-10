#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
#include <stdio.h>


#ifndef DEFINE_INITTT
#define DEFINE_INITTT

#define UNDEFINED 0

#define SCREENROWS 24
#define SCREENCOLS 39

#define MENUCOLS 41

#define FOVROWS 21
#define FOVCOLS 35

#define WORLDROWS 75
#define WORLDCOLS 231

#define SOLIDCOUNT 5
#define WALKABLECOUNT 3

#endif //DEFINE_INITTT

#ifndef STRUCT_INIT
#define STRUCT_INIT

struct mob
{
	int row;
	int col;
	bool up;
	bool down;
	bool right;
	bool left;
	int health;	
};

struct map
{
	char texture;
	bool solid;
	bool walkable;
	bool mapInView;
	bool mapIsEdge;
};

struct fov
{
	bool inView;
	bool isEdge;
	bool isPlayer;
};

struct line                          //line = (m * x) + b
{
	double mSlope;
	double bIntercept;
};

struct koordinate
{
	double x;
	double y;
};

//struct in
//{
//	bool w;
//	bool s;
//	bool a;
//	bool d;
//	bool esc;
//};

#endif //STRUCT INIT
