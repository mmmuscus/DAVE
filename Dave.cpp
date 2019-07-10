#include "headers/system/system.h"

#include "headers/debug/debug.h"


#include "headers/input/input.h"


#include "headers/output/output.h"
#include "headers/output/movement.h"


#include "headers/rendering/render.h"
#include "headers/rendering/shadowFunctions.h"
#include "headers/rendering/animation.h"


//using namespace std;

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
	
	player.up = false;
	player.down = false;
	player.right = true;
	player.left = false;
	
	//init lastPlayer
	mob lastPlayer;
	lastPlayer.row = player.row;
	lastPlayer.col = player.col;
	
	//init camera
	mob camera;
	camera = camMovement(camera, player);
//	camera.row = player.row - 12;
//	camera.col = player.col - 3;
	
	//init whereToCamera (where to move camera)
	mob whereToCamera;
	whereToCamera.row = camera.row;
	whereToCamera.col = camera.col;
	
	mob playerInFov;
	
	koordinate playerPov;
	
	edgeLines edges;
	
	
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
	
	initFOV(right, "FOVs/right.txt");
	initFOV(left, "FOVs/left.txt");
	initFOV(down, "FOVs/down.txt");
	initFOV(up, "FOVs/up.txt");
	initFOV(rightDown, "FOVs/rightDown.txt");
	initFOV(rightUp, "FOVs/rightUp.txt");
	initFOV(leftDown, "FOVs/leftDown.txt");
	initFOV(leftUp, "FOVs/leftUp.txt");
	
	setCurrentFov(player, currentFov, right, left, up, down, rightUp, rightDown, leftUp, leftDown);
	
	playerInFov = getPlayerPosInFov(player, playerInFov);
	
	playerPov = getPov(playerPov, player);
	
	char solid[SOLIDCOUNT];
	char walkable[WALKABLECOUNT];
	
	initSolid(solid, "materials/solid.txt");
	initWalkable(walkable, "materials/walkable.txt");
	
	map newWorld[WORLDROWS][WORLDCOLS];
//	map oldWorld[WORLDROWS][WORLDCOLS];

	initWorld(newWorld, solid, walkable, "maps/world.txt");
	
	animation logo = initNewAnimation(logo, "animations/logo.txt");
	int frame = 0;
	
	//gmae lööp
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
		
		//SHADOW FUNCTIONS IS DONE BELOW:
		playerPov = getPov(playerPov, player);
	
		//DEBUG RIGHT HERE:
		goTo(0, 0);
	
		//&&& edges is felesleges RIGHT HERE BELOW
		shadowFunction(newWorld, camera.col, camera.row, playerPov, edges);
		holePlugger(newWorld, camera.col, camera.row);
		
		mapIsEdgeCalculation(newWorld, camera.row, camera.col);
		
		//Filling up the screen for rendering :OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
		//this is filling out mapIsEdge
		calculateScreen(newWorld, newScreen, camera.row, camera.col);
		
		if (newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] == playerTexture)
		{		
			newScreen[lastPlayer.row - camera.row][lastPlayer.col - camera.col] = ' ';
		}
		newScreen[player.row - camera.row][player.col - camera.col] = playerTexture;
		
		for (int i = 0; i < SCREENROWS; i++)
		{
			newMenu[i][0] = screenDivisionTexture;
		}
		
		renderScreen(oldScreen, newScreen);
		
		renderMenu(oldMenu, newMenu);
		
		playAnimation(logo, frame, 0, 40);
		if (frame < logo.frames)
		{
			frame++;
		}
		
		goTo(0, 0);
		cout<<frame;
	}
	
	//END OF THE GAME LOOP
	
	//Debug!!!!
	clearScreen();
	
//	drawTestMap(newWorld);
//	
//	drawTestSolid(newWorld);
//	
//	drawTestWalkable(newWorld);
//	
//	drawTestFov(up);
//	
//	drawTestInView(newWorld);

//	screenShot(newScreen);

//	frameDraw();
	
//	animationArrayTest(logo);
	
	return 0;
}
