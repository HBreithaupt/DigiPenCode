/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      GameStateManager.c
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        function definitions to handle the state of the game
History
 - 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved. 
---------------------------------------------------------------------------- */
#include "GameStateManager.h"
#include "GameStateList.h"
#include "Level1.h"
#include "Level2.h"
#include "System.h"

int Current;
int Previous;
int Next;

void GSM_Initialize(int InitLevel)
{
	if (InitLevel = 1)
	{
		Current = Level_1;
		Previous = Level_1;
		Next = Level_1;
	}
	else if (InitLevel = 2)
	{
		Current = Level_2;
		Previous = Level_2;
		Next = Level_2;
	}
	else
	{
		Current = Level_1;
		Previous = Level_1;
		Next = Level_1;
	}

	fprintf(output, "GSM:Initialize\n");
}

void GSM_Update(void)
{
	if (Current == Level_1)
	{
		pLoad = &Load1;
		pInitialize = &Init1;
		pUpdate = &Update1;
		pDraw = &Draw1;
		pFree = &Free1;
		pUnload = &Unload1;
	}

	if (Current == Level_2)
	{
		pLoad = &Load2;
		pInitialize = &Init2;
		pUpdate = &Update2;
		pDraw = &Draw2;
		pFree = &Free2;
		pUnload = &Unload2;
	}

	fprintf(output, "GSM:Update\n");
	
}