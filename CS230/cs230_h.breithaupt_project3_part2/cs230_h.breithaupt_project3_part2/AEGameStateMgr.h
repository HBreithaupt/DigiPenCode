// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEGameStateMgr.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2007/10/26
// Purpose			:	header file for the game state manager
// History			:
// - 2007/10/26		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_GAME_STATE_MGR_H
#define AE_GAME_STATE_MGR_H

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// defines and enums

#define AE_GS_RESTART	0xFFFFFFFE
#define AE_GS_QUIT		0xFFFFFFFF


// ---------------------------------------------------------------------------
// externs

extern AE_API u32	gAEGameStateInit;
extern AE_API u32	gAEGameStateCurr;
extern AE_API u32	gAEGameStatePrev;
extern AE_API u32	gAEGameStateNext;

// ---------------------------------------------------------------------------

extern AE_API void (*AEGameStateLoad)(void);
extern AE_API void (*AEGameStateInit)(void);
extern AE_API void (*AEGameStateUpdate)(void);
extern AE_API void (*AEGameStateDraw)(void);
extern AE_API void (*AEGameStateFree)(void);
extern AE_API void (*AEGameStateUnload)(void);

// ---------------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------------

#ifdef __cplusplus

extern "C"
{
#endif
// ---------------------------------------------------------------------------

// function to add new game state to the manager
AE_API void AEGameStateMgrAdd(u32 gameStateIdx, void (*pLoad)(), void (*pInit)(), void (*pUpdate)(), void (*pDraw)(), void (*pFree)(), void (*pUnload)());

// call this at the beginning and AFTER all game states are added to the manager
AE_API void AEGameStateMgrInit(u32 gameStateInit);

// update is used to set the function pointers
AE_API void AEGameStateMgrUpdate();

// ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // AE_GAME_STATE_MGR_H