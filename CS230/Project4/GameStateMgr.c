// ---------------------------------------------------------------------------
// Project Name		:	Cage Game
// File Name		:	GameState_Menu.cpp
// Author			:	Antoine Abi Chakra
// Creation Date	:	2012/03/16
// Purpose			:	implementation of the game state manager
// History			:
// - 
// ---------------------------------------------------------------------------

#include "GameStateMgr.h"

#include "GameState_Play.h"

// ---------------------------------------------------------------------------
// globals

// variables to keep track the current, previous and next game state
u32	gGameStateInit;
u32	gGameStateCurr;
u32	gGameStatePrev;
u32	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)()		= 0;
void (*GameStateInit)()		= 0;
void (*GameStateUpdate)()	= 0;
void (*GameStateDraw)()		= 0;
void (*GameStateFree)()		= 0;
void (*GameStateUnload)()	= 0;

// ---------------------------------------------------------------------------
// Functions implementations

void GameStateMgrInit(u32 gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = 
	gGameStatePrev = 
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

// ---------------------------------------------------------------------------

void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_PLAY:
		GameStateLoad	= GameStatePlayLoad;
		GameStateInit	= GameStatePlayInit;
		GameStateUpdate	= GameStatePlayUpdate;
		GameStateDraw	= GameStatePlayDraw;
		GameStateFree	= GameStatePlayFree;
		GameStateUnload	= GameStatePlayUnload;
		break;

	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}

// ---------------------------------------------------------------------------
