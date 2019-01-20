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
	
	edgeLines edges;
	
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
		
		//elõször végigmegyek vízszintesen mindent s mindennkit leárnyékolok akit le kell 
		//aztán végigmegyek függõlegesen s megint leárnyékolok mindent s mindenkit akit le kell.....
		
		//&&& IMPORTANT FOR DEBUGGING SHADOW FUNCTIONS !!! rossz oszlopban érzékeli a player charactert!!!!
		
		//A GARAND REWRITE IS NEEDED
		
//		for (int i = 0; i < SCREENROWS; i++)
//		{
//			for (int j = 0; j < SCREENCOLS; j++)
//			{
//				if (newWorld[i + camera.row][j + camera.col].mapInView && newWorld[i + camera.row][j + camera.col].solid)
//				{
//					//get line equations
//					lineA = getLineOfSight(playerPov, i + camera.row, i + camera.row + 1, j + camera.col + 1, j + camera.col, lineB, false);
//					lineB = getLineOfSight(playerPov, i + camera.row, i + camera.row + 1, j + camera.col + 1, j + camera.col, lineA, true);
//					
//					goTo(0, 0);
//					cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<lineA.mSlope<<") + "<<lineA.bIntercept;
//					goTo(1, 0);
//					cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<lineB.mSlope<<") + "<<lineB.bIntercept;
//					
//					//sg is not rite...
//					
//					for (int g = 0; g < SCREENROWS; g++)
//					{
//						for (int h = 0; h < SCREENCOLS; h++)
//						{
//							if (isWhollyInShadow(lineA, lineB, g + camera.row, h + camera.col) && g != i && h != j)
//							{
//								newWorld[g + camera.row][h + camera.col].mapInView = false;
//							}
//						}
//					}
//				}
//			}
//		}

//		lineA = getFirstLine(playerPov, 35, 36, 60, 61);
//		lineB = getSecondLine(playerPov, 35, 36, 60, 61);

		//valamiért néha lineA = lineB ezt nem kéne engedni...
//		lineA = getLineOfSight(playerPov, 35, 36, 72, 60, lineB, false);
//		lineB = getLineOfSight(playerPov, 35, 36, 72, 60, lineA, true);
//		
//		goTo(0, 0);
//		cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<lineA.mSlope<<") + "<<lineA.bIntercept<<" ENDL";
//		goTo(1, 0);
//		cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<lineB.mSlope<<") + "<<lineB.bIntercept<<" ENDL";
//		
//		//testing isWhollyInShadow
//		for (int g = 0; g < SCREENROWS; g++)
//		{
//			for(int h = 0; h < SCREENCOLS; h++)
//			{
//				if (isWhollyInShadow(lineA, lineB, g + camera.row, h + camera.col) && !newWorld[g + camera.row][h + camera.col].solid)
//				{
//					newWorld[g + camera.row][h + camera.col].mapInView = false;
//				}
//			}
//		}
		
		//testing isBehindWall
		//UPDATE its working well most propably
//		for (int g = 0; g < SCREENROWS; g++)
//		{
//			for(int h = 0; h < SCREENCOLS; h++)
//			{
//				if (isBehindWall(playerPov, g + camera.row, h + camera.col, 35, 36, 72, 60) && !newWorld[g + camera.row][h + camera.col].solid)
//				{
//					newWorld[g + camera.row][h + camera.col].mapInView = false;
//				}
//			}
//		}

		//LETS TEST THE GETLINEEQUATION FUNCTION WITH A BUTA AF FUNCTION
		edges = butaAF(playerPov, 35, 36, 72, 60);
		
		goTo(0, 0);
		cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<edges.first.mSlope<<") + "<<edges.first.bIntercept<<" ENDL";
		goTo(1, 0);
		cout<<playerPov.y<<" = ("<<playerPov.x<<" * "<<edges.second.mSlope<<") + "<<edges.second.bIntercept<<" ENDL";
		
		//testing isWhollyInShadow
		for (int g = 0; g < SCREENROWS; g++)
		{
			for(int h = 0; h < SCREENCOLS; h++)
			{
				if (isWhollyInShadow(edges.first, edges.second, g + camera.row, h + camera.col) && !newWorld[g + camera.row][h + camera.col].solid)
				{
					newWorld[g + camera.row][h + camera.col].mapInView = false;
				}
			}
		}
		
//		for (int i = 0; i < SCREENROWS; i++)
//		{
//			int j = 0;
//			
//			while (j < SCREENCOLS)
//			{
//				if (newWorld[i + camera.row][j + camera.col].mapInView && newWorld[i + camera.row][j + camera.col].solid)
//				{
//					int k = 0;
//					
//					while (newWorld[i + camera.row][j + camera.col + k].mapInView && newWorld[i + camera.row][j + camera.col + k].solid)
//					{
//						k++;
//					}
//					
//					//REWRITE TIME FOTHERFUCKER!!!!!!!!!!!
//					
////					goTo(i, 0);
////					wallBlockingLight = getRectangleEdges(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col - 1, j + camera.col);
//					//ha egy sorba van a cuccal akkor top = bottom és right = left, ha alatta vagy felette van akkor pedig teljesen megõrül
//					//balról jobbra nézva ami a player alatt van annak a right és left felcserélõdik
//					//jobbról balra nézve ami a player felett van annak a right és left felcserélõdik
//					//&&&                                                              REWRITE azt ami megszerzi a sarkokat!!! think about ur smart algorythm!!! jeeez my man! !!!getLineOfSight this is in actual shadow functions!!!
//					//top one:		left: 62 top: 31 right: 65 bottom: 30
//					//middle one:	left: 60 top: 35 right: 72 bottom: 36
//					//bottom one:	left: 67 top: 39 right: 69 bottom: 40
////					cout<<wallBlockingLight.a.x<<" top: "<<wallBlockingLight.a.y<<" "<<wallBlockingLight.b.x<<" bot: "<<wallBlockingLight.b.y;
////					cout<<"t: "<<i + camera.row<<" b: "<<i + camera.row + 1<<" l: "<<j + camera.col<<" r: "<<j + k + camera.col;               //!!!   ezeket az értékeket kéne átadni a funkciónak ami a vonalakat számolja
//					
//					//két vonal ami közrefogja a téglalapot ezt az egészet 2 függvényben meg tudom oldani yay
//					
//					//MIT KÉNE CSINÁLNI? aka NEW CODE PLAN                                !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//					//eddig megvan a téglalapunk és a point of viewnk
//					//meg kell határozni a két vonalat ami köztefogja, ezt a getLineOfSight fügvénnyel meg tudom oldani, lehet hogy bezavar az hogy abban is van egy int i? dunno will find out but keep an eye out for that case
//					//el kell döntenem hogy mi esik a fal mögé, és mi esik a fal elé hogy mit is kéne eltakarnom
//					//amit el kell takarnom azt belenyomkodom a newWorldbe hogy  a rendering megoldja 
//					
//					//NEW CODE:
//					
//					//get line equations:
//					lineA = getLineOfSight(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col, j + camera.col, lineB, false);
//					lineB = getLineOfSight(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col, j + camera.col, lineA, true);
//					
//					//what is behind the wall:
//					//prolly gonna do it simulatneously with the rendering preparations
//					//rewriting isBehindWall
//					//done with rewriting isBehindWall
//					//need to rewrite isWhollyInShadow
//					//it is done probably
//					
//					for (int g = 0; g < SCREENROWS; g++)
//					{
//						for (int h = 0; h < SCREENCOLS; h++)
//						{
//							if (/*isWhollyInShadow(lineA, lineB, g + camera.row, h + camera.col) && */isBehindWall(playerPov, g + camera.row, h + camera.col, i + camera.row, i + camera.row + 1, j + k + camera.col, j + camera.col))
//							{   // is it between the shadows, and is it behind the wall
//								newWorld[g + camera.row][h + camera.col].mapInView = false;
//							}
//						}
//					}
//					
//					//isBehindWall: a falak is le vannak árnyékolva dunno why
//					//isWhollyInShadow: ha felette s balra van akkor tökéletesen mükszik ha simán felette van akkor meghal lehet hogy azzal van abaja hogy nincs in view a cucc but dunno...
//					
//					//not quite good but hey its..something
//					
//					//OLD CODE:
////					lineA = getLineEquation(playerPov.x, playerPov.y, wallBlockingLight.a.x, wallBlockingLight.a.y);
////					lineAOverLine = isLineOverLine(lineA, i + camera.row + 0.5, j + camera.col + 0.5);
////					lineB = getLineEquation(playerPov.x, playerPov.y, wallBlockingLight.b.x, wallBlockingLight.b.y);
////					lineBOverLine = isLineOverLine(lineB, i + camera.row + 0.5, j + camera.col + 0.5);
////					
////					isPlayerNextTo = isPlayerNextToRectangle(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col);
////					isPlayerOverOrUnder = isPlayerOverOrUnderRectangle(playerPov, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col);
////					
////					for (int g = 0; g < SCREENROWS; g++)
////					{
////						for (int h = 0; h < SCREENCOLS; h++)
////						{
////							if (isWhollyInShadow(lineA, lineB, lineAOverLine, lineBOverLine, g + camera.row, h + camera.col))
////							{
////								if (isBehindWall(playerPov, g + camera.row, h + camera.col, isPlayerNextTo, isPlayerOverOrUnder, i + camera.row, i + camera.row + 1, j + k + camera.col + 1, j + camera.col))
////								{
////									newWorld[g + camera.row][h + camera.col].mapInView = false;
////								}  //isBehindWall is probably not working right
////							}
////						}
////					}
//
//					//what became obselete:
//					//isPlayerNextTo isPlayerNextToRectangle
//					//isPlayerUnderOrOver isPlayerUnderOrOverRectangle
//					//wallBlockingLIght getRectangleEdges
//					//lineAOverline lineBOverline isLineOverline
//					
//					j = j + k;   //comment this shit out at the endt dud!
//				}
//				else
//				{
//					j++;
//				}
//			}
//		}
		
		//end of shadow functions
		
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
		
//		goTo(0, 0);
//		cout<<"row: "<<player.row<<" col: "<<player.col;
//		goTo(1, 0);
//		cout<<"row: "<<playerPov.y<<" col: "<<playerPov.x;
	}
	
	//END OF THE GAME LOOP
	
	//Debug!!!!
	clearScreen();
	
	drawTestMap(newWorld);
	
	drawTestSolid(newWorld);
	
	drawTestWalkable(newWorld);
	
	drawTestFov(up);
	
	drawTestInView(newWorld);
	
	return 0;
}
