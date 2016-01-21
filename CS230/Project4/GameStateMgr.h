// ---------------------------------------------------------------------------
// Project Name		:	Cage Game
// File Name		:	GameStateMgr.h
// Author			:	Antoine Abi Chakra
// Creation Date	:	2012/03/16
// Purpose			:	header file for the game state manager
// History			:
// - 
// ---------------------------------------------------------------------------

#ifndef GAME_STATE_MGR_H
#define GAME_STATE_MGR_H

// ---------------------------------------------------------------------------

#include "AEEngine.h"

// ---------------------------------------------------------------------------
// include the list of game states

#include "GameStateList.h"

// ---------------------------------------------------------------------------
// externs

extern u32 gGameStateInit;
extern u32 gGameStateCurr;
extern u32 gGameStatePrev;
extern u32 gGameStateNext;

// ---------------------------------------------------------------------------

extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

// ---------------------------------------------------------------------------
// Function prototypes

// call this at the beginning and AFTER all game states are added to the manager
void GameStateMgrInit(u32 gameStateInit);

// update is used to set the function pointers
void GameStateMgrUpdate();

// ---------------------------------------------------------------------------

#endif // AE_GAME_STATE_MGR_H