// ---------------------------------------------------------------------------
// Project Name		:	Cage Game
// File Name		:	GameState_Menu.cpp
// Author			:	Antoine Abi Chakra
// Creation Date	:	2012/03/16
// Purpose			:	implementation of the 'play' game state
// History			:
// - 
// ---------------------------------------------------------------------------

#include "main.h"

// ---------------------------------------------------------------------------
// Defines

#define GAME_OBJ_NUM_MAX			32
#define GAME_OBJ_INST_NUM_MAX		1024

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// object flag definition

#define FLAG_ACTIVE		0x00000001

#define TEST_PART_2				0
#define DRAW_DEBUG				1									// Set this to 1 in order to draw debug data


#define LINE_SEGMENTS_NUM		5									// Don't change
#define BALL_RADIUS				15.0f
#define PILLARS_NUM				6									// Don't change


// ---------------------------------------------------------------------------

// Game object types
enum
{
	TYPE_BALL,
	TYPE_LINE,
};

// ---------------------------------------------------------------------------
// Struct/Class definitions

typedef struct 
{
	u32					type;		// object type
	AEGfxVertexList		*pMesh;		// pbject
}GameObj;

// ---------------------------------------------------------------------------

typedef struct 
{
	GameObj*		pObject;	// pointer to the 'original'
	u32				flag;		// bit flag or-ed together
	f32				life;		// object 'life'
	f32				scaleX;
	f32				scaleY;
	Vector2D			posCurr;	// object current position
	Vector2D			velCurr;	// object current velocity
	f32				dirCurr;	// object current direction

	AEMtx33			transform;	// object drawing matrix

	// pointer to custom data specific for each object type
	void*			pUserData;
}GameObjInst;

// ---------------------------------------------------------------------------
// Static variables

// list of original object
static GameObj			sGameObjList[GAME_OBJ_NUM_MAX];
static u32				sGameObjNum;

// list of object instances
static GameObjInst		sGameObjInstList[GAME_OBJ_INST_NUM_MAX];
static u32				sGameObjInstNum;

static Vector2D			gRoomPoints[LINE_SEGMENTS_NUM * 2];
static LineSegment2D	gRoomLineSegments[LINE_SEGMENTS_NUM];

#if(TEST_PART_2)

static Vector2D			gPillarsCenters[PILLARS_NUM];
static float			gPillarsRadii[PILLARS_NUM];
static LineSegment2D	gPillarsWalls[PILLARS_NUM / 2];

#endif

static GameObjInst		*pBall;
static GameObjInst		*pBallVelocity;
// ---------------------------------------------------------------------------

// function to 'load' object data
static void			loadGameObjList();

// function to create/destroy a game object object
static GameObjInst*	gameObjInstCreate (u32 type, f32 scaleX, f32 scaleY, Vector2D* pPos, Vector2D* pVel, f32 dir);
static void			gameObjInstDestroy(GameObjInst* pInst);


static int			sgStopped = 0;

// ---------------------------------------------------------------------------

void GameStatePlayLoad(void)
{
	unsigned int i;
	// zero the game object list
	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);
	sGameObjNum = 0;

	// zero the game object instance list
	memset(sGameObjInstList, 0, sizeof(GameObjInst) * GAME_OBJ_INST_NUM_MAX);
	sGameObjInstNum = 0;

	
	// load/create the mesh data
	loadGameObjList();


	// Building map boundaries
	Vector2DSet(&gRoomPoints[0], -350.0f, 100.0f);		Vector2DSet(&gRoomPoints[1], 0, 250.0f);
	Vector2DSet(&gRoomPoints[2], 0, 250.0f);				Vector2DSet(&gRoomPoints[3], 350.0f, 100.0f);
	Vector2DSet(&gRoomPoints[4], 350.0f, 100.0f);			Vector2DSet(&gRoomPoints[5], 275.0f, -250.0f);
	Vector2DSet(&gRoomPoints[6], 275.0f, -250.0f);		Vector2DSet(&gRoomPoints[7], -275.0f, -250.0);
	Vector2DSet(&gRoomPoints[8], -275.0f, -250.0f);		Vector2DSet(&gRoomPoints[9], -350.0f, 100.0f);

	// Build line segments
	for(i = 0; i < LINE_SEGMENTS_NUM; ++i)
		BuildLineSegment2D(&gRoomLineSegments[i], &gRoomPoints[i*2], &gRoomPoints[i*2 + 1]);


#if(TEST_PART_2)
	// Pillars
	Vector2DSet(&gPillarsCenters[0], -200.0f, 0.0f);
	gPillarsRadii[0] = 15;
	
	Vector2DSet(&gPillarsCenters[1], -150.0f, 100.0f);
	gPillarsRadii[1] = 20;
	
	Vector2DSet(&gPillarsCenters[2], -100.0f, -150.0f);
	gPillarsRadii[2] = 15;

	Vector2DSet(&gPillarsCenters[3], 100.0f, -175.0f);
	gPillarsRadii[3] = 10;
	
	Vector2DSet(&gPillarsCenters[4], 175.0f, 100.0f);
	gPillarsRadii[4] = 20;
	
	Vector2DSet(&gPillarsCenters[5], 225.0f, -25.0f);
	gPillarsRadii[5] = 10;

	// Pillars walls
	for(i = 0; i < PILLARS_NUM/2; ++i)
		BuildLineSegment2D(&gPillarsWalls[i], &gPillarsCenters[i*2], &gPillarsCenters[i*2 + 1]);

#endif
}

// ---------------------------------------------------------------------------

void GameStatePlayInit(void)
{
	unsigned int i;

	pBall = gameObjInstCreate(TYPE_BALL, BALL_RADIUS*2, BALL_RADIUS*2, NULL, NULL, 0);
 
	Vector2DSet(&pBall->posCurr, 0.0f, 0.0f);
	Vector2DSet(&pBall->velCurr, 120.0f, 155.0f);

	// Wall instances
	for(i = 0; i < LINE_SEGMENTS_NUM; ++i)
	{	
		float length, angle;
		Vector2D v;

		length = Vector2DDistance(&gRoomPoints[2*i], &gRoomPoints[2*i + 1]);
		
		Vector2DSub(&v, &gRoomPoints[2*i + 1], &gRoomPoints[2*i]);
		Vector2DNormalize(&v, &v);
		
		angle = atan2(v.y, v.x);
		gameObjInstCreate(TYPE_LINE, length, 5.0f, (Vector2D *)(&gRoomPoints[2 * i]), NULL, angle);
	}

#if(TEST_PART_2)
	// Segments between pillars instances, and pillars instances
	for(i = 0; i < (PILLARS_NUM >> 1); ++i)
	{	
		float length, angle;
		Vector2D v;

		// segments
		length = Vector2DDistance(&gPillarsCenters[2*i], &gPillarsCenters[2*i + 1]);
	
		Vector2DSub(&v, &gPillarsCenters[2*i + 1], &gPillarsCenters[2*i]);
		Vector2DNormalize(&v, &v);
		
		angle = atan2(v.y, v.x);
		gameObjInstCreate(TYPE_LINE, length, 5.0f, (Vector2D *)(&gPillarsCenters[2*i]), NULL, angle);


		// Pillars
		gameObjInstCreate(TYPE_BALL, gPillarsRadii[2*i]*2, gPillarsRadii[2*i]*2, (Vector2D *)(&gPillarsCenters[2*i]), NULL, 0);
		gameObjInstCreate(TYPE_BALL, gPillarsRadii[2*i + 1]*2, gPillarsRadii[2*i + 1]*2, (Vector2D *)(&gPillarsCenters[2*i + 1]), NULL, 0);
	}
#endif

#if(DRAW_DEBUG)

	// Normals of the outer lines
	for(i = 0; i < LINE_SEGMENTS_NUM; ++i)
	{	
		Vector2D v, pos;
		float angle;

		Vector2DSub(&v, &gRoomPoints[2*i + 1], &gRoomPoints[2*i]);
		Vector2DNormalize(&v, &v);

		pos.x = (gRoomPoints[2*i].x + gRoomPoints[2*i + 1].x) / 2.0f;
		pos.y = (gRoomPoints[2*i].y + gRoomPoints[2*i + 1].y) / 2.0f;

		angle = atan2(v.x, -v.y);
		gameObjInstCreate(TYPE_LINE, 25.0f, 5.0f, (Vector2D *)(&pos), NULL, angle);
	}

	pBallVelocity = gameObjInstCreate(TYPE_LINE, 50.0f, 1.0f, NULL, NULL, 0.0f);

#if(TEST_PART_2)
	// Normals of the inner lines
	for(i = 0; i < (PILLARS_NUM >> 1); ++i)
	{	
		Vector2D v, pos;
		float angle;

		Vector2DSub(&v, &gPillarsCenters[2*i + 1], &gPillarsCenters[2*i]);
		Vector2DNormalize(&v, &v);

		pos.x = (gPillarsCenters[2*i].x + gPillarsCenters[2*i + 1].x) / 2.0f;
		pos.y = (gPillarsCenters[2*i].y + gPillarsCenters[2*i + 1].y) / 2.0f;

		angle = atan2(v.x, -v.y);
		gameObjInstCreate(TYPE_LINE, 25.0f, 5.0f, (Vector2D *)(&pos), NULL, angle);
	}
#endif

#endif

	
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

// ---------------------------------------------------------------------------

void GameStatePlayUpdate(void)
{
	float smallestT;
	Vector2D closestIntersectionPoint, r;
	unsigned int i;
	Vector2D newBallPos;
	Vector2D intersectionPoint;


	float frameTime = AEFrameRateControllerGetFrameTime();
	int stopStep = 0;

	if (0 == sgStopped)
	{
		if (AEInputCheckTriggered('S')) // 'S' to stop the simulation
			sgStopped = 1;
	}
	else
	{
		if (AEInputCheckTriggered('R'))	// 'R' to let the simulation run
			sgStopped = 0;
		else
		if (AEInputCheckTriggered('S'))	// 1 step per 'S' trigger
		{
			frameTime = 0.016f;
			stopStep = 1;
		}
		else
		if (AEInputCheckCurr('G'))		// Simulation runs as long as 'G' is pressed
		{
			frameTime = 0.016f;
			stopStep = 1;
		}
	}

	if (0 == sgStopped || 1 == stopStep)
	{

		// =================
		// update the input
		// =================

		// Update the positions of objects

		Vector2DScaleAdd(&newBallPos, &pBall->velCurr, &pBall->posCurr, frameTime);


		smallestT = -1.0f;

		// Collision with line segments
		for(i = 0; i < LINE_SEGMENTS_NUM; ++i)
		{
			float t = ReflectAnimatedCircleOnStaticLineSegment(&pBall->posCurr, &newBallPos, BALL_RADIUS, &gRoomLineSegments[i], &intersectionPoint, &r);

			if(t > 0.0f && (t < smallestT || smallestT < 0.0f))
			{
				closestIntersectionPoint = intersectionPoint;
				smallestT = t;
			}
		}

#if(TEST_PART_2)

		// Collision with pillars (Static circles)
		for(i = 0; i < PILLARS_NUM; ++i)
		{
			float t = AEReflectAnimatedCircleOnStaticCircle(&pBall->posCurr, &newBallPos, BALL_RADIUS, &gPillarsCenters[i], gPillarsRadii[i], &intersectionPoint, &r);

			if(t > 0.0f && (t < smallestT || smallestT < 0.0f))
			{
				closestIntersectionPoint = intersectionPoint;
				smallestT = t;
			}
		}

		// Collision with pillars' walls (Line segments between the static circles)
		for (i = 0; i < PILLARS_NUM / 2; ++i)
		{
			float t = ReflectAnimatedCircleOnStaticLineSegment(&pBall->posCurr, &newBallPos, BALL_RADIUS, &gPillarsWalls[i], &intersectionPoint, &r);

			if (t > 0.0f && (t < smallestT || smallestT < 0.0f))
			{
				closestIntersectionPoint = intersectionPoint;
				smallestT = t;
			}
		}

#endif

		if (smallestT > 0.0)
		{
			Vector2DAdd(&pBall->posCurr, &closestIntersectionPoint, &r);
			Vector2DNormalize(&r, &r);
			Vector2DScale(&pBall->velCurr, &r, Vector2DLength(&pBall->velCurr));
		}

		Vector2DScaleAdd(&pBall->posCurr, &pBall->velCurr, &pBall->posCurr, frameTime);


#if(DRAW_DEBUG)
		{
			float cosine, sine, velLength, angle;

			velLength = Vector2DLength(&pBall->velCurr);
			cosine = pBall->velCurr.x / velLength;
			sine = pBall->velCurr.y / velLength;

			angle = acosf(cosine);

			if (sine < 0)
				angle = -angle;

			Vector2DSet(&pBallVelocity->posCurr, pBall->posCurr.x, pBall->posCurr.y);
			pBallVelocity->dirCurr = angle;
		}

#endif

	}


	// =====================================
	// calculate the matrix for all objects
	// =====================================

	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		AEMtx33		 m;
		GameObjInst* pInst = sGameObjInstList + i;
		

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		
		AEMtx33Scale		(&pInst->transform, pInst->scaleX,     pInst->scaleY);
		AEMtx33Rot			(&m,                pInst->dirCurr);
		AEMtx33Concat		(&pInst->transform, &m,               &pInst->transform);
		AEMtx33Trans		(&m,                pInst->posCurr.x, pInst->posCurr.y);
		AEMtx33Concat		(&pInst->transform, &m,               &pInst->transform);
	}
}

// ---------------------------------------------------------------------------

void GameStatePlayDraw(void)
{
	s8 strBuffer[1024];
	unsigned int i;

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	// draw all object in the list
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInst* pInst = sGameObjInstList + i;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;
		
		AEGfxSetTransform	(sGameObjInstList[i].transform.m);

		if (TYPE_LINE == pInst->pObject->type)
			AEGfxMeshDraw(sGameObjInstList[i].pObject->pMesh, AE_GFX_MDM_LINES);
		else
			AEGfxMeshDraw(sGameObjInstList[i].pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

// ---------------------------------------------------------------------------

void GameStatePlayFree(void)
{
	unsigned int i;
	// kill all object in the list
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		gameObjInstDestroy(sGameObjInstList + i);
}

// ---------------------------------------------------------------------------

void GameStatePlayUnload(void)
{
	unsigned int i;

	// free all mesh
	for (i = 0; i < sGameObjNum; i++)
		AEGfxMeshFree(sGameObjList[i].pMesh);
}

// ---------------------------------------------------------------------------
// Static function implementations

static void loadGameObjList()
{
	unsigned int i;
	float CircleAngleStep;
	int Parts;
	GameObj* pObj;

	// ===============
	// create the ball
	// ===============
	pObj		= sGameObjList + sGameObjNum++;
	pObj->type	= TYPE_BALL;

	AEGfxMeshStart();
	CircleAngleStep = PI/12.0f, i;
	Parts = 24;
	for(i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
		0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf(i*2*PI/Parts)*0.5f,  sinf(i*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f, 
		cosf((i+1)*2*PI/Parts)*0.5f,  sinf((i+1)*2*PI/Parts)*0.5f, 0xFFFFFF00, 0.0f, 0.0f);
	}

	pObj->pMesh = AEGfxMeshEnd();

	// ===============
	// create the line
	// ===============
	pObj = sGameObjList + sGameObjNum++;
	pObj->type = TYPE_LINE;

	AEGfxMeshStart();

	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(1.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	pObj->pMesh = AEGfxMeshEnd();
}

// ---------------------------------------------------------------------------

GameObjInst* gameObjInstCreate(u32 type, f32 scaleX, f32 scaleY, Vector2D* pPos, Vector2D* pVel, f32 dir)
{
	unsigned int i;
	Vector2D zero = { 0.0f, 0.0f };

	//AE_ASSERT_PARM(type < sGameObjNum);
	
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
			pInst->life		 = 1.0f;
			pInst->scaleX	 = scaleX;
			pInst->scaleY	 = scaleY;
			pInst->posCurr	 = pPos ? *pPos : zero;
			pInst->velCurr	 = pVel ? *pVel : zero;
			pInst->dirCurr	 = dir;
			pInst->pUserData = 0;
			
			// return the newly created instance
			return pInst;
		}
	}

	// cannot find empty slot => return 0
	return 0;
}

// ---------------------------------------------------------------------------

void gameObjInstDestroy(GameObjInst* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;
}

// ---------------------------------------------------------------------------
