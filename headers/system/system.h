#include <windows.h>
#include <iostream>
#include <fstream>
#include <winnt.h>
#include <stdio.h>
#include <String>
using namespace std;

#ifndef DEFINE_INIT
#define DEFINE_INIT

#define SCREENCOLS 39

#define MENUCOLS 41

#define CONSOLEROWS 24
#define CONSOLECOLS 80

#define FOVROWS 21
#define FOVCOLS 35

#define WORLDROWS 87
#define WORLDCOLS 231

#define SOLIDCOUNT 5
#define WALKABLECOUNT 3

#define INFINITECIMAL 0.000001

#define MAXAMOUNTOFANIMATIONFRAMES 500

#endif //DEFINE_INIT

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
	bool isItUnderLine;
};

struct edgeLines
{
	line first;
	line second;
};

struct koordinate
{
	double x;
	double y;
};

struct animation
{
	int frames;
	int height;
	int width;
	char frameArray[MAXAMOUNTOFANIMATIONFRAMES][CONSOLEROWS][CONSOLECOLS];
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
