// ---------------------------------------------------------------------------
// Project Name		:	Cage Game
// File Name		:	GameStateList.h
// Author			:	Antoine Abi Chakra
// Creation Date	:	2012/03/16
// Purpose			:	header file for the game state list enum
// History			:
// - 
// ---------------------------------------------------------------------------

#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

// ---------------------------------------------------------------------------
// game state list

enum
{
	// list of all game states
	GS_PLAY    = 0, 
	
	// special game state. Do not change
	GS_RESTART,
	GS_QUIT, 
	GS_NUM
};

// ---------------------------------------------------------------------------

#endif // GAME_STATE_LIST_H