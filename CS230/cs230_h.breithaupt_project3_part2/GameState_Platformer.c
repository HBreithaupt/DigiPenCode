// ---------------------------------------------------------------------------
// Project Name		:	Platformer
// File Name		:	GameState_Platformer.cpp
// Author			:	Haven Breithaupt
// Creation Date	:	3-9-2015
// Purpose			:	Implementation of the platform game state
// History			:
//	- 3/9-15 completed all but enemy state machine
//	- 3/11/15 completed project
// © Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------


#include "AEEngine.h"
#include "GameStateMgr.h"
#include "Math2D.h"
#include "Matrix2D.h"

// ---------------------------------------------------------------------------
#pragma warning(disable: 4996)

#define GAME_OBJ_NUM_MAX			32
#define GAME_OBJ_INST_NUM_MAX		2048

//Gameplay related variables and values
#define GRAVITY -20.0f
#define JUMP_VELOCITY 11.0f
#define MOVE_VELOCITY_HERO 4.0f
#define MOVE_VELOCITY_ENEMY 7.5f
#define ENEMY_IDLE_TIME 2.0
#define HERO_LIVES 3
#define MAPSCALE 30  /* scale of the map for the transform matrix*/
static int HeroLives;
static int Hero_Initial_X;
static int Hero_Initial_Y;
static int TotalCoins;

//Flags
#define FLAG_ACTIVE			0x00000001


enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN			//4
};

//State machine states
enum STATE
{
	STATE_NONE,
	STATE_GOING_LEFT,
	STATE_GOING_RIGHT
};

//State machine inner states
enum INNER_STATE
{
	INNER_STATE_ON_ENTER,
	INNER_STATE_ON_UPDATE,
	INNER_STATE_ON_EXIT
};


typedef struct
{
	unsigned int		type;		// object type
	AEGfxVertexList*	pMesh;		// pbject
}GameObj;


typedef struct
{
	GameObj*		pObject;	// pointer to the 'original'
	unsigned int	flag;		// bit flag or-ed together
	float			scale;
	Vector2D			posCurr;	// object current position
	Vector2D			velCurr;	// object current velocity
	float			dirCurr;	// object current direction

	Matrix2D			transform;	// object drawing matrix

	//Used to hold the current 
	int				gridCollisionFlag;

	// pointer to custom data specific for each object type
	void*			pUserData;

	//State of the object instance
	enum			STATE state;
	enum			INNER_STATE innerState;

	//General purpose counter (This variable will be used for the enemy state machine)
	double			counter;
}GameObjInst;


// list of original objects
static GameObj			*sGameObjList;
static unsigned int		sGameObjNum;

// list of object instances
static GameObjInst		*sGameObjInstList;
static unsigned int		sGameObjInstNum;

//Binary map data
static int **MapData;
static int **BinaryCollisionArray;
static int BINARY_MAP_WIDTH;
static int BINARY_MAP_HEIGHT;
static Matrix2D MapTransform;
int GetCellValue(int X, int Y);
int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY);
void SnapToCell(float *Coordinate);
int ImportMapDataFromFile(char *FileName);
void FreeMapData(void);


//Collision flags
#define	COLLISION_LEFT		0x00000001	//0001
#define	COLLISION_RIGHT		0x00000002	//0010
#define	COLLISION_TOP		0x00000004	//0100
#define	COLLISION_BOTTOM	0x00000008	//1000



// function to create/destroy a game object instance
static GameObjInst*	gameObjInstCreate (unsigned int type, float scale, Vector2D* pPos, Vector2D* pVel, float dir, enum STATE startState);
static void			gameObjInstDestroy(GameObjInst* pInst);

//We need a pointer to the hero's instance for input purposes
static GameObjInst *pHero;

//State machine functions
void EnemyStateMachine(GameObjInst *pInst);


void GameStatePlatformLoad(void)
{
	// USed for the cicle shape
	float CircleAngleStep, i;
	int Parts;
	GameObj* pObj;
	Matrix2D mapScale, mapTrans;


	sGameObjList = (GameObj *)calloc(GAME_OBJ_NUM_MAX, sizeof(GameObj));
	sGameObjInstList = (GameObjInst *)calloc(GAME_OBJ_INST_NUM_MAX, sizeof(GameObjInst));
	sGameObjNum = 0;



	//Creating the black object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_EMPTY;

	AEGfxMeshStart();

	//1st argument: X
	//2nd argument: Y
	//3rd argument: ARGB
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0xFF000000, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFF000000, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFF000000, 0.0f, 0.0f, 
		 0.5f,  0.5f, 0xFF000000, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();

		
	
	//Creating the white object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_COLLISION;

	AEGfxMeshStart();

	//1st argument: X
	//2nd argument: Y
	//3rd argument: ARGB
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFFFFFF, 0.0f, 0.0f, 
		 0.5f,  0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();


	//Creating the hero object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_HERO;

	AEGfxMeshStart();

	//1st argument: X
	//2nd argument: Y
	//3rd argument: ARGB
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFF0000FF, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFF0000FF, 0.0f, 0.0f, 
		 0.5f,  0.5f, 0xFF0000FF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();


	//Creating the enemey1 object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_ENEMY1;

	AEGfxMeshStart();

	//1st argument: X
	//2nd argument: Y
	//3rd argument: ARGB
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		-0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f);
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		 0.5f,  -0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		 0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();


	//Creating the Coin object
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_OBJECT_COIN;

	AEGfxMeshStart();

	//1st argument: X
	//2nd argument: Y
	//3rd argument: ARGB

	//Creating the circle shape
	CircleAngleStep = PI/12.0f;
	Parts = 12;
	for(i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
		0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf(i*2*PI/Parts)*0.5f,  sinf(i*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf((i+1)*2*PI/Parts)*0.5f,  sinf((i+1)*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f);
	}

	pObj->pMesh = AEGfxMeshEnd();

	//Setting intital binary map values
	MapData = 0;
	BinaryCollisionArray = 0;
	BINARY_MAP_WIDTH = 0;
	BINARY_MAP_HEIGHT = 0;

	//Importing Data
	if(!ImportMapDataFromFile("Exported.txt"))
		gGameStateNext = GS_QUIT;


	//Computing the matrix which take a point out of the normalized coordinates system
	//of the binary map
	/*********** COMPLETE
	Compute a transformation matrix and save it in "MapTransform".
	This transformation transforms any point from the normalized coordinates system of the binary map.
	Later on, when rendering each object instance, we should concatenate "MapTransform" with the
	object instance's own transformation matrix

	Compute a translation matrix (-Grid width/2, -Grid height/2) and save it in "mapTrans"
	Compute a scaling matrix and save it in "mapScale")
	Concatenate scale * translate and save the result in "MapTransform"
	***********/
  
    Matrix2DTranslate(&mapTrans, -BINARY_MAP_WIDTH/2, -BINARY_MAP_HEIGHT/2);
    Matrix2DScale(&mapScale, MAPSCALE, MAPSCALE);
  
    Matrix2DConcat(&MapTransform, &mapScale, &mapTrans);

	
}

void GameStatePlatformInit(void)
{
	int i, j;
	GameObjInst *pInst;
	Vector2D Pos;

	pHero = 0;
	TotalCoins = 0;

	//Setting the inital number of hero lives
	HeroLives = HERO_LIVES;

	// Creating the map, the main character, the enemies and the coins according to their initial positions in MapData

	/*********** COMPLETE
	Loop through all the array elements of MapData (which was initialized in the "GameStatePlatformLoad" function
	from the .txt file
		
		 - Create a white or black cell

		 - if the element represents the hero
			Create a hero instance
			Set its position depending on its array indices in MapData
			Save its array indices in Hero_Initial_X and Hero_Initial_Y (Used when the hero dies and its position needs to be reset)

		 - if the element represents an enemy
			Create an enemy instance
			Set its position depending on its array indices in MapData
			
		 - if the element represents a coin
			Create a coin instance
			Set its position depending on its array indices in MapData



			
	***********/
	for (int b = 0; b < BINARY_MAP_WIDTH; ++b)
	{
		for (int c = 0; c < BINARY_MAP_HEIGHT; ++c)
		{
			Vector2D Pos = { b + 0.5, c + 0.5 };
			Vector2D Vel = { 0 };


			/* black cell*/
			if (MapData[b][c] != 1)
				gameObjInstCreate(TYPE_OBJECT_EMPTY, 1, &Pos, &Vel, 0, STATE_NONE);

			/* white cell*/
			if (MapData[b][c] == 1)
				gameObjInstCreate(TYPE_OBJECT_COLLISION, 1, &Pos, &Vel, 0, STATE_NONE);
		}
	}

	for (i = 0; i < BINARY_MAP_WIDTH; ++i)
	{
		for (j = 0; j < BINARY_MAP_HEIGHT; ++j)
		{
		
			Vector2D Pos = { i + 0.5 , j + 0.5};
			Vector2D Vel = { 0 };

				/* hero */
			if (MapData[i][j] == 2)
			{
				pHero = gameObjInstCreate(TYPE_OBJECT_HERO, 1, &Pos, &Vel, 0, STATE_NONE);

				Hero_Initial_X = i + 0.5;
				Hero_Initial_Y = j + 0.5;
			}

				/* coin */
			if (MapData[i][j] == 4)
			{
				gameObjInstCreate(TYPE_OBJECT_COIN, 1, &Pos, &Vel, 0, STATE_NONE);
				TotalCoins++;

			}
				
			/* enemy */
			if (MapData[i][j] == 3)
				gameObjInstCreate(TYPE_OBJECT_ENEMY1, 1, &Pos, &Vel, 0, STATE_GOING_LEFT);
				

			
		}
	}
}

void GameStatePlatformUpdate(void)
{
	freopen("CONOUT$", "w", stdout);
	int i, j;
	GameObjInst *pInst;
	float winMaxX, winMaxY, winMinX, winMinY;
	double frameTime;
	
	// ==========================================================================================
	// Getting the window's world edges (These changes whenever the camera moves or zooms in/out)
	// ==========================================================================================
	winMaxX = AEGfxGetWinMaxX();
	winMaxY = AEGfxGetWinMaxY();
	winMinX = AEGfxGetWinMinX();
	winMinY = AEGfxGetWinMinY();


	// ======================
	// Getting the frame time
	// ======================

	frameTime = AEFrameRateControllerGetFrameTime();

	//Handle Input
	/*********** COMPLETE
	if right is pressed
		Set hero velocity X to MOVE_VELOCITY_HERO
	else
	if left is pressed
		Set hero velocity X to -MOVE_VELOCITY_HERO
	else
		Set hero velocity X to 0

	if space is pressed AND Hero is colliding from the bottom
		Set hero velocity Y to JUMP_VELOCITY

	if q is pressed
		Exit game
	***********/

	if (AEInputCheckCurr(VK_RIGHT))
		pHero->velCurr.x = MOVE_VELOCITY_HERO;
	else if (AEInputCheckCurr(VK_LEFT))
		pHero->velCurr.x = -MOVE_VELOCITY_HERO;
	else
		pHero->velCurr.x = 0;

	if (AEInputCheckCurr(VK_SPACE) && (pHero->gridCollisionFlag & COLLISION_BOTTOM))
		pHero->velCurr.y = JUMP_VELOCITY;

	/* press q to quit */
	if (AEInputCheckTriggered('Q'))
		gGameStateNext = GS_QUIT;

	/* press r to restart*/
	if (AEInputCheckTriggered('R'))
		gGameStateNext = GS_RESTART;

	//Update object instances physics and behavior
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		GameObjInst *pInst = sGameObjInstList + i;

				// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_ENEMY1)
			EnemyStateMachine(pInst);
		
		if (pInst->pObject->type != TYPE_OBJECT_HERO)
			continue;
			
		/**************** HALF COMPLETE
		Apply gravity
			Velcoty Y = Gravity * Frame Time + Velocity Y

		If object instance is an enemy
			Apply enemy state machine
		****************/

		
		pInst->velCurr.y = GRAVITY * frameTime + pInst->velCurr.y;
	}

	//Update object instances positions
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		GameObjInst *pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		/********** COMPLETE
		update the position using: P1 = V1*t + P0
		**********/

		Vector2D NewPos; 
		Vector2DScaleAdd(&NewPos, &pInst->velCurr, &pInst->posCurr, frameTime);

		pInst->posCurr = NewPos;
	}

	//Check for grid collision
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		GameObjInst *pInst = sGameObjInstList + i;



		// skip non-active object instances
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_EMPTY ||
			pInst->pObject->type == TYPE_OBJECT_COLLISION)
			continue;

		/*************
		Update grid collision flag

		if collision from bottom
			Snap to cell on Y axis
			Velocity Y = 0

		if collision from top
			Snap to cell on Y axis
			Velocity Y = 0
	
		if collision from left
			Snap to cell on X axis
			Velocity X = 0

		if collision from right
			Snap to cell on X axis
			Velocity X = 0
		*************/

		pInst->gridCollisionFlag = CheckInstanceBinaryMapCollision(pInst->posCurr.x, pInst->posCurr.y, pInst->scale, pInst->scale);

		if (pInst->gridCollisionFlag & COLLISION_BOTTOM ||
			pInst->gridCollisionFlag & COLLISION_TOP)
		{
			SnapToCell(&pInst->posCurr.y);
			pInst->velCurr.y = 0;
		}

		if (pInst->gridCollisionFlag & COLLISION_LEFT ||
			pInst->gridCollisionFlag & COLLISION_RIGHT)
		{
			SnapToCell(&pInst->posCurr.x);
			pInst->velCurr.x = 0;
		}
		
		

	}


	//Checking for collision among object instances:
	//Hero against enemies
	//Hero against coins

	/**********
	for each game object instance
		Skip if it's inactive or if it's non collidable

		If it's an enemy
			If collision between the enemy instance and the hero (rectangle - rectangle)
				Decrement hero lives
				Reset the hero's position in case it has lives left, otherwise restart the level

		If it's a coin
			If collision between the coin instance and the hero (circle - rectangle)
				Remove the coin and decrement the coin counter.
				Quit the game in case no more coins are left
	**********/
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		GameObjInst *pInst = sGameObjInstList + i;

		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_EMPTY || pInst->pObject->type == TYPE_OBJECT_COLLISION || pInst->pObject->type == TYPE_OBJECT_HERO)
			continue;

		if (pInst->pObject->type == TYPE_OBJECT_COIN)
		{
		
			if (StaticCircleToStaticRectangle(&pInst->posCurr, pInst->scale, &pHero->posCurr, pHero->scale, pHero->scale))
			{
				pInst->flag = 0;
				TotalCoins--;

				if (TotalCoins == 0)
					gGameStateNext = GS_QUIT;
			}
		}

		if (pInst->pObject->type == TYPE_OBJECT_ENEMY1)
		{
			if (StaticRectToStaticRect(&pHero->posCurr, pHero->scale / 2, pHero->scale / 2, &pInst->posCurr, pInst->scale / 2, pInst->scale / 2))
			{
				HeroLives--;

				if (HeroLives == 0)
					gGameStateNext = GS_RESTART;
				else
				{
					pHero->posCurr.x = Hero_Initial_X;
					pHero->posCurr.y = Hero_Initial_Y;
				}
			}
		} 

	}

	
	//Computing the transformation matrices of the game object instances
	for(i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		Matrix2D scale, rot, trans;
		GameObjInst *pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;

		Matrix2DScale(&scale, pInst->scale, pInst->scale);
		Matrix2DRotDeg(&rot, pInst->dirCurr);
		Matrix2DTranslate(&trans, pInst->posCurr.x, pInst->posCurr.y);

		Matrix2DConcat(&pInst->transform, &trans, &rot);
		Matrix2DConcat(&pInst->transform, &pInst->transform, &scale);
	}
}

void GameStatePlatformDraw(void)
{
	//Drawing the tile map (the grid)
	int i, j;
	Matrix2D cellTranslation, cellFinalTransformation;
	double frameTime;
	char strBuffer[100];

	/* background is red for the sake of seeing the white cells that border the game */
	AEGfxSetBackgroundColor(1.0f, 0.0f, 0.0f);


	// ======================
	// Getting the frame time
	// ======================

	frameTime = AEFrameRateControllerGetFrameTime();

	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);


	//Drawing the tile map

	/******REMINDER*****
	You need to concatenate MapTransform with the transformation matrix of any object you want to draw.
	MapTransform transform the instance from the normalized coordinates system of the binary map
	*******************/


	//Drawing the object instances
	/**********
	For each active and visible object instance
		Concatenate MapTransform with its transformation matrix
		Send the resultant matrix to the graphics manager using "AEGfxSetTransform"
		Draw the instance's shape using "AEGfxMeshDraw"
	**********/
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// skip non-active object
		if (0 == (pInst->flag & FLAG_ACTIVE))
			continue;


		
		//Don't forget to concatenate the MapTransform matrix with the transformation of each game object instance
		Matrix2DConcat(&pInst->transform, &MapTransform, &pInst->transform);
		AEGfxSetTransform(pInst->transform.m);
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}


void GameStatePlatformFree(void)
{
	unsigned int i;
	// kill all object in the list
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		gameObjInstDestroy(sGameObjInstList + i);
}

void GameStatePlatformUnload(void)
{
	unsigned int i;
	// free all CREATED mesh
	for (i = 0; i < sGameObjNum; i++)
		AEGfxMeshFree(sGameObjList[i].pMesh);

	/*********
	Free the map data
	*********/

	FreeMapData();
}


GameObjInst* gameObjInstCreate(unsigned int type, float scale, Vector2D* pPos, Vector2D* pVel, float dir, enum STATE startState)
{
	unsigned int i;
	Vector2D zero = { 0.0f, 0.0f };

	AE_ASSERT_PARM(type < sGameObjNum);
	
	// loop through the object instance list to find a non-used object instance
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject	 = sGameObjList + type;
			pInst->flag		 = FLAG_ACTIVE;
			pInst->scale	 = scale;
			pInst->posCurr	 = pPos ? *pPos : zero;
			pInst->velCurr	 = pVel ? *pVel : zero;
			pInst->dirCurr	 = dir;
			pInst->pUserData = 0;
			pInst->gridCollisionFlag = 0;
			pInst->state = startState;
			pInst->innerState = INNER_STATE_ON_ENTER;
			pInst->counter = 0;
			
			// return the newly created instance
			return pInst;
		}
	}
}

void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}

int GetCellValue(int X, int Y)
{
    if(X < 0 || Y < 0)
      return 0;
  
    if(X >= (unsigned)BINARY_MAP_WIDTH || Y >= (unsigned)BINARY_MAP_HEIGHT)
      return 0;
	
    return BinaryCollisionArray[X][Y];
}


int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
	//At the end of this function, "Flag" will be used to determine which sides
	//of the object instance are colliding. 2 hot spots will be placed on each side.
	
  int Flag = 0;
  
  float xr1, yr1, xr2, yr2, xl1, yl1, xl2, yl2, xt1, yt1, xt2, yt2, xb1, yb1, xb2, yb2;
  
  /* right hotspots */
    
    /* right top*/
  xr1 = PosX + scaleX/2;
  yr1 = PosY + scaleY/4;
    
    /* right bottom */
  xr2 = PosX + scaleX/2;
  yr2 = PosY - scaleY/4;
  
  /* left hotspots */
    
    /* left top */
  xl1 = PosX - scaleX/2;
  yl1 = PosY + scaleY/4;
    
    /* left bottom */
  xl2 = PosX - scaleX/2;
  yl2 = PosY - scaleX/4;
    
  /* top hotspots */
    
    /* top right */
  xt1 = PosX + scaleX/4;
  yt1 = PosY + scaleY/2;
  
    /* top left */
  xt2 = PosX - scaleX/4;
  yt2 = PosY + scaleY/2;
    
  /* bottom hotspots */
  
    /* bottom right */
  xb1 = PosX + scaleX/4;
  yb1 = PosY - scaleY/2;
  
    /* bottom left */
  xb2 = PosX - scaleX/4;
  yb2 = PosY - scaleY/2;
	
  /* check for right collision */
  if (GetCellValue((int)xr1, (int)yr1) == 1 || GetCellValue((int)xr2, (int)yr2) == 1)
  Flag |= COLLISION_RIGHT;
  
  
  /* check for left collision */
  if (GetCellValue((int)xl1, (int)yl1) == 1 || GetCellValue((int)xl2, (int)yl2) == 1)
  Flag |= COLLISION_LEFT;
  
  
  /* check for top collision */
  if (GetCellValue((int)xt1, (int)yt1) == 1 || GetCellValue((int)xt2, (int)yt2) == 1)
  Flag |= COLLISION_TOP;
  
  
  /* check for bottom collision */
  if (GetCellValue((int)xb1, (int)yb1) == 1 || GetCellValue((int)xb2, (int)yb2) == 1)
  Flag |= COLLISION_BOTTOM;
  
  
  return Flag;
}


void SnapToCell(float *Coordinate)
{
  *Coordinate = (int)*Coordinate + 0.5f;
}

int ImportMapDataFromFile(char *FileName)
{
	FILE *fp;
	
	fp = fopen(FileName, "r");
	int input;
  
    if(fp)
    {
      fscanf(fp, "Width %i\n", &BINARY_MAP_WIDTH);
      fscanf(fp, "Height %i", &BINARY_MAP_HEIGHT);
      
      MapData = (int **) malloc(BINARY_MAP_HEIGHT * sizeof(int));
      BinaryCollisionArray = (int **) malloc(BINARY_MAP_HEIGHT * sizeof(int));

	  for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	  {
		  MapData[i] = (int *)malloc(BINARY_MAP_WIDTH * sizeof(int));
		  BinaryCollisionArray[i] = (int *)malloc(BINARY_MAP_WIDTH * sizeof(int));
	  }
      
      for(int row = BINARY_MAP_HEIGHT - 1; row >= 0; row--)
      {
        for(int column = 0;  column < BINARY_MAP_WIDTH; column++)
        {
			fscanf(fp, "%i", &input);

			MapData[column][row] = input;

			if (input > 1)
				BinaryCollisionArray[column][row] = 0;
			else
				BinaryCollisionArray[column][row] = input;
        }
      }
      
     
	  fclose(fp);
      return 1;
      
    }
    else
    {
      return 0;
    }
}


void FreeMapData(void)
{
  for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		free(MapData[i]);
		free(BinaryCollisionArray[i]);
	}

	free(MapData);
	free(BinaryCollisionArray);
}

void EnemyStateMachine(GameObjInst *pInst)
{
	/***********
	This state machine has 2 states: STATE_GOING_LEFT and STATE_GOING_RIGHT
	Each state has 3 inner states: INNER_STATE_ON_ENTER, INNER_STATE_ON_UPDATE, INNER_STATE_ON_EXIT
	Use "switch" statements to determine which state and inner state the enemy is currently in.


	STATE_GOING_LEFT
		INNER_STATE_ON_ENTER
			Set velocity X to -MOVE_VELOCITY_ENEMY
			Set inner state to "on update"

		INNER_STATE_ON_UPDATE
			If collision on left side OR bottom left cell is non collidable
				Initialize the counter to ENEMY_IDLE_TIME
				Set inner state to on exit
				Set velocity X to 0


		INNER_STATE_ON_EXIT
			Decrement counter by frame time
			if counter is less than 0 (sprite's idle time is over)
				Set state to "going right"
				Set inner state to "on enter"

	STATE_GOING_RIGHT is basically the same, with few modifications.

	***********/
	switch (pInst->state)
	{
		case (STATE_GOING_LEFT) : 
		{
			switch (pInst->innerState)
			{
			case (INNER_STATE_ON_ENTER) :
				pInst->velCurr.x = -MOVE_VELOCITY_ENEMY;
				pInst->innerState = INNER_STATE_ON_UPDATE;
				break;

			case (INNER_STATE_ON_UPDATE) :
				if (pInst->gridCollisionFlag & COLLISION_LEFT ||
					GetCellValue(pInst->posCurr.x - 1, pInst->posCurr.y - 1) == TYPE_OBJECT_EMPTY)
				{
				pInst->counter = ENEMY_IDLE_TIME;
				pInst->velCurr.x = 0;
				pInst->innerState = INNER_STATE_ON_EXIT;
				SnapToCell(&pInst->posCurr.x);
				}
				break;

			case (INNER_STATE_ON_EXIT) :
			{
				double frametime = AEFrameRateControllerGetFrameTime();

				pInst->counter -= frametime;

				if (pInst->counter <= 0)
				{
					pInst->state = STATE_GOING_RIGHT;
					pInst->innerState = INNER_STATE_ON_ENTER;
				}
			}
			break;

			}
		}
		break;
		
		case (STATE_GOING_RIGHT) :
		{

			switch (pInst->innerState)
			{
			case (INNER_STATE_ON_ENTER) :
				pInst->velCurr.x = MOVE_VELOCITY_ENEMY;
				pInst->innerState = INNER_STATE_ON_UPDATE;
				break;

			case (INNER_STATE_ON_UPDATE) :
				if (pInst->gridCollisionFlag & COLLISION_RIGHT ||
					GetCellValue(pInst->posCurr.x + 1, pInst->posCurr.y - 1) == TYPE_OBJECT_EMPTY)
				{
				pInst->counter = ENEMY_IDLE_TIME;
				pInst->velCurr.x = 0;
				pInst->innerState = INNER_STATE_ON_EXIT;
				SnapToCell(&pInst->posCurr.x);
				}
				break;

			case (INNER_STATE_ON_EXIT) :
			{
				double frametime = AEFrameRateControllerGetFrameTime();

				pInst->counter -= frametime;

				if (pInst->counter <= 0)
				{
					pInst->state = STATE_GOING_LEFT;
					pInst->innerState = INNER_STATE_ON_ENTER;
				}
			}
			break;
			}
		}
		break;

	}
}