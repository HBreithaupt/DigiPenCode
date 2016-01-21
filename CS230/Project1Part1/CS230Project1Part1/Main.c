/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      Main.c
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        Runs the game loop
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */

#include "System.h"
#include "GameStateManager.h"
#include "GameStateList.h"
#include "Input.h"
#include "FrameRateController.h"

#pragma warning(disable: 4996)

void main(void)
{
	System_Initialize();

	GSM_Initialize(1);

	while (Current != Quit)
	{

		FrameInitialization();

		if (Current == Restart)
		{
			Current = Previous;
			Next = Previous;
		}
		else
		{
			GSM_Update();
			pLoad();
		}

		pInitialize();

		while (Current == Next)
		{
			FrameControllerStart();
			Input_Handle();
			pUpdate();
			pDraw();
			FrameControllerEnd();
		}

		pFree();

		if (Next != Restart)
		{
			pUnload();
		}

		Previous = Current;
		Current = Next;
	}

	System_Exit();
}