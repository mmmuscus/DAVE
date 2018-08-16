#include "headers/system/system.h"

#include "headers/debug/debug.h"


#include "headers/input/input.h"


#include "headers/output/output.h"
#include "headers/output/movement.h"


#include "headers/rendering/render.h"
#include "headers/rendering/shadowFunctions.h"
#include "headers/rendering/actualShadowFunctions.h"


using namespace std;

const double height = /*2.16*/ 1.0;
const double width = /*1.4375*/ 1.0;

const char playerTexture = '@';
const char screenDivisionTexture = '#';

int main()
{	
	//INPUT
	
//	in input;
	
	bool isWPressed;
	bool isSPressed;
	bool isAPressed;
	bool isDPressed;
	bool isEscPressed;
	
	
	//OUTPUT
	
	//init player
	mob player;
	player.row = 35;
	player.col = 45;
	player.health = UNDEFINED;
	player.up = false;
	player.down = false;
	player.right = true;
	player.left = false;
	
	//init lastPlayer
	mob lastPlayer;
	lastPlayer.row = player.row;
	lastPlayer.col = player.col;
//	lastPlayer.health = UNDEFINED;
	
	//init camera
	mob camera;
	camera.row = player.row - 12;
	camera.col = player.col - 3;
//	camera.health = UNDEFINED;
	
	//init whereToCamera (where to move camera)
	mob whereToCamera;
	whereToCamera.row = camera.row;
	whereToCamera.col = camera.col;
	
	mob playerInFov;
	
	koordinate playerPov;
	
	rectangle wallBlockingLight;
	
	line lineA;
	bool lineAOverLine;
	line lineB;
	bool lineBOverLine;
	
	bool isPlayerNextTo;
	bool isPlayerOverOrUnder;
	
	
	//RENDER
	
	int sleepTime = 30;
	
	bool isNotExit = true;
	
	char oldScreen[SCREENROWS][SCREENCOLS];                       //dont ask why this is the way it is but it is the way it is and the way it is it works so... IDK IDC IDGAF            pOSTsCRIPT: pHUCKtHISbUGtOhELL
	char newScreen[SCREENROWS][SCREENCOLS];
	
	char oldMenu[SCREENROWS][MENUCOLS];
	char newMenu[SCREENROWS][MENUCOLS];
	
	fov right[FOVROWS][FOVCOLS];
	fov left[FOVROWS][FOVCOLS];
	fov up[FOVROWS][FOVCOLS];
	fov down[FOVROWS][FOVCOLS];
	fov rightUp[FOVROWS][FOVCOLS];
	fov rightDown[FOVROWS][FOVCOLS];
	fov leftUp[FOVROWS][FOVCOLS];
	fov leftDown[FOVROWS][FOVCOLS];
	
	fov currentFov[FOVROWS][FOVCOLS];
	
	initRight(right);
	initLeft(left);
	initUp(up);
	initDown(down);
	initRightUp(rightUp);
	initRightDown(rightDown);
	initLeftUp(leftUp);
	initLeftDown(leftDown);
	
	makeCurrentFov(right, currentFov);
	
	playerInFov = getPlayerPosInFov(player, playerInFov);
	
	playerPov = getPov(playerPov, player, height, width);
	
	char solid[SOLIDCOUNT];
	char walkable[WALKABLECOUNT];
	
	initSolid(solid);
	initWalkable(walkable);
	
	map newWorld[WORLDROWS][WORLDCOLS];
//	map oldWorld[WORLDROWS][WORLDCOLS];

	initWorld(newWorld, solid, walkable);
	
	while (isNotExit)
	{
		Sleep(sleepTime);
		
		
		//INPUT
		
		isWPressed = false;
		isAPressed = false;
		isSPressed = false;
		isDPressed = false;
		isEscPressed = false;
		
		isWPressed = wPressed();
		isAPressed = aPressed();
		isSPressed = sPressed();
		isDPressed = dPressed();
		isEscPressed = escPressed();

//		getInput(input);

		cancelOut(isWPressed, isSPressed);
		cancelOut(isAPressed, isDPressed);
		
		
		//OUTPUT

		saveLastScreenArray(oldScreen, newScreen);
		
		saveLastMenuArray(oldMenu, newMenu);
		
		if (isEscPressed)
		{
			isNotExit = false;
		}
		
		lastPlayer.row = player.row;
		lastPlayer.col = player.col;
		
		//PLAYER HANDLEING
		
		player = playerMovement(player, isWPressed, isSPressed, isAPressed, isDPressed);
		player = keepInBounds(player, lastPlayer, newWorld);
		player = setDirections(player, isWPressed, isSPressed, isAPressed, isDPressed);
		
		//CAMERA HANDLEING
		
		whereToCamera = camMovement(whereToCamera, player);
		camera = cameraPan(camera, whereToCamera);                                                                             //&&& SLOWPAN OR FASTPAN??????????????????????????????,
		camera = keepCamInBounds(camera, newWorld);
		
		//FOV HANDLEING
		
		setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
		playerInFov = getPlayerPosInFov(player, playerInFov);
		addFovInfoToMap(newWorld, player, playerInFov, currentFov);
		
		// X COL    Y ROW OMG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		//SHADOW FUNCTIONS
		
		playerPov = getPov(playerPov, player, height, width);
		
		//el�sz�r v�gigmegyek v�zszintesen mindent s mindennkit le�rny�kolok akit le kell 
		//azt�n v�gigmegyek f�gg�legesen s megint le�rny�kolok mindent s mindenkit akit le kell.....
		
		//&&& IMPORTANT FOR DEBUGGING SHADOW FUNCTIONS !!! rossz oszlopban �rz�keli a player charactert!!!!
		
		for (int i = 0; i < SCREENROWS; i++)
		{
			int j = 0;
			
			while (j < SCREENCOLS)
			{
				if (newWorld[i + camera.row][j + camera.col].mapInView && newWorld[i + camera.row][j + camera.col].solid)
				{
					int k = 0;
					
					while (newWorld[i + camera.row][j + camera.col + k].mapInView && newWorld[i + camera.row][j + camera.col + k].solid)
					{
						k++;
					}
					
					//REWRITE TIME FOTHERFUCKER!!!!!!!!!!!
					
					goTo(i, 0);
					wallBlockingLight = getRectangleEdges(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col - 1, j + camera.col);
					//ha egy sorba van a cuccal akkor top = bottom �s right = left, ha alatta vagy felette van akkor pedig teljesen meg�r�l
					//balr�l jobbra n�zva ami a player alatt van annak a right �s left felcser�l�dik
					//jobbr�l balra n�zve ami a player felett van annak a right �s left felcser�l�dik
					//top one:		left: 62 top: 31 right: 64 bottom: 30
					//middle one:	left: 60 top: 35 right: 71 bottom: 36
					//bottom one:	left: 67 top: 39 right: 68 bottom: 40
					cout<<wallBlockingLight.a.x<<" top: "<<wallBlockingLight.a.y<<" "<<wallBlockingLight.b.x<<" bot: "<<wallBlockingLight.b.y;
					
					//k�t vonal ami k�zrefogja a t�glalapot ezt az eg�szet 2 f�ggv�nyben meg tudom oldani yay
					
					lineA = getLineEquation(playerPov.x, playerPov.y, wallBlockingLight.a.x, wallBlockingLight.a.y);
					lineAOverLine = isLineOverLine(lineA, i + camera.row + 0.5, j + camera.col + 0.5);
					lineB = getLineEquation(playerPov.x, playerPov.y, wallBlockingLight.b.x, wallBlockingLight.b.y);
					lineBOverLine = isLineOverLine(lineB, i + camera.row + 0.5, j + camera.col + 0.5);
					
					isPlayerNextTo = isPlayerNextToRectangle(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col);
					isPlayerOverOrUnder = isPlayerOverOrUnderRectangle(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col);
					
					for (int g = 0; g < SCREENROWS; g++)
					{
						for (int h = 0; h < SCREENCOLS; h++)
						{
							if (isWhollyInShadow(lineA, lineB, lineAOverLine, lineBOverLine, g + camera.row, h + camera.col))
							{
								if (isBehindWall(playerPov, g + camera.row, h + camera.col, isPlayerNextTo, isPlayerOverOrUnder, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col))
								{
									newWorld[g + camera.row][h + camera.col].mapInView = false;
								}
							}
						}
					}
					
					j = j + k;   //comment this shit out at the endt dud!
				}
				else
				{
					j++;
				}
			}
		}
		
		//Filling up the screen for rendering :OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

		for (int i = 0; i < SCREENROWS; i++)
		{
			for (int j = 0; j < SCREENCOLS; j++)
			{
				if (newWorld[i + camera.row][j + camera.col].mapInView)
				{
					if (newWorld[i + camera.row][j + camera.col].mapIsEdge)
					{
							newScreen[i][j] = char(176);
					}
					else
					{
						newScreen[i][j] = newWorld[i + camera.row][j + camera.col].texture;
					}
				}
				else
				{
					newScreen[i][j] = char(178);
				}
			}
		}
		
		if (newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] == playerTexture)
		{		
			newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] = ' ';
		}
		newScreen[player.row - camera.row][player.col - camera.col] = playerTexture;
		
		for (int i = 0; i < SCREENROWS; i++)
		{
			newMenu[i][0] = screenDivisionTexture;
		}
		
		//RENDER IT IS DONE...MAYBE...PROBABLY THO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		renderScreen(oldScreen, newScreen);
		
		renderMenu(oldMenu, newMenu);
		
		goTo(0, 0);
		cout<<"row: "<<player.row<<" col: "<<player.col;
		goTo(1, 0);
		cout<<"row: "<<playerPov.y<<" col: "<<playerPov.x;
	}
	
	//Debug!!!!
	clearScreen();
	
	drawTestMap(newWorld);
	
	drawTestSolid(newWorld);
	
	drawTestWalkable(newWorld);
	
	drawTestFov(up);
	
	drawTestInView(newWorld);
	
	return 0;
}
