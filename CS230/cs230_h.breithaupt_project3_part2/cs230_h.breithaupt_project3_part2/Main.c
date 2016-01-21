// ---------------------------------------------------------------------------
// Project Name		:	Platformer
// File Name		:	main.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2007/04/26
// Purpose			:	main entry point for the test program
// History			:
// - 2007/04/26		:	- initial implementation
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes
#include "AEEngine.h"
#include "GameStateMgr.h"

// Libraries
#pragma comment (lib, "Alpha_Engine.lib")
// ---------------------------------------------------------------------------
// Static function protoypes


// ---------------------------------------------------------------------------
// main

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Initialize the system 
	AESysInitInfo sysInitInfo;

	sysInitInfo.mCreateWindow			= 1;
	sysInitInfo.mWindowHandle			= NULL;
	sysInitInfo.mAppInstance			= instanceH;
	sysInitInfo.mShow					= show;
	sysInitInfo.mWinWidth				= 1280; 
	sysInitInfo.mWinHeight				= 800;
	sysInitInfo.mCreateConsole			= 1;
	sysInitInfo.mMaxFrameRate			= 60;
	sysInitInfo.mpWinCallBack			= NULL;
	sysInitInfo.mClassStyle				= CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle			= WS_OVERLAPPEDWINDOW;
	sysInitInfo.mHandleWindowMessages	= 1;

	if(0 == AESysInit (&sysInitInfo))
		return 1;

	GameStateMgrInit(GS_PLATFORMER);

	while(gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();

		// If not restarting, load the gamestate
		if(gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		// Initialize the gamestate
		GameStateInit();

		while(gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

			AEInputUpdate();

			GameStateUpdate();

			GameStateDraw();
			
			AESysFrameEnd();

			// check if forcing the application to quit
			if (AEInputCheckTriggered(VK_ESCAPE))
					gGameStateNext = GS_QUIT;
		}
		
		GameStateFree();

		if(gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	// free the system
	AESysExit();
}

// ---------------------------------------------------------------------------