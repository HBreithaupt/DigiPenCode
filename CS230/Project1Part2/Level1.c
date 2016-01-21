/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      Level1.c
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        Contains function definitions for all level 1 components
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */

#include "Level1.h"
#include "System.h"
#include "GameStateManager.h"
#include "GameStateList.h"




void Load1(void)
{
	fprintf(output, "Level1:Load\n");
}

void Init1(void)
{
	fprintf(output, "Level1:Initialize\n");
}

void Update1(void)
{
	fprintf(output, "Level1:Update\n");
}

void Draw1(void)
{
	fprintf(output, "Level1:Draw\n");
}

void Free1(void)
{
	fprintf(output, "Level1:Free\n");
}

void Unload1(void)
{
	fprintf(output, "Level1:Unload\n");
}
