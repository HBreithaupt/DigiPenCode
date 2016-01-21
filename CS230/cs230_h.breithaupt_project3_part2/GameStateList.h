// ---------------------------------------------------------------------------
// Project Name		:	Asteroid
// File Name		:	GameStateList.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/02/08
// Purpose			:	game state list for the asteroid game
// History			:
// - 2007/02/08		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

// ---------------------------------------------------------------------------
// game state list

enum
{
	// list of all game states 
	GS_PLATFORMER = 0, 
	
	// special game state. Do not change
	GS_RESTART,
	GS_QUIT, 
	GS_NUM
};

// ---------------------------------------------------------------------------

#endif // GAME_STATE_LIST_H