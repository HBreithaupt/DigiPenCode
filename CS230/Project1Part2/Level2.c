/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      Level2.c
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        Contains function definitions for all level 2 components
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */

#include "Level2.h"
#include "System.h"
#include "GameStateManager.h"
#include "GameStateList.h"


void Load2(void)
{
	fprintf(output, "Level2:Load\n");
}

void Init2(void)
{
	fprintf(output, "Level2:Initialize\n");
}

void Update2(void)
{
	fprintf(output, "Level2:Update\n");
}

void Draw2(void)
{
	fprintf(output, "Level2:Draw\n");
}

void Free2(void)
{
	fprintf(output, "Level2:Free\n");
}

void Unload2(void)
{
	fprintf(output, "Level2:Unload\n");
}
