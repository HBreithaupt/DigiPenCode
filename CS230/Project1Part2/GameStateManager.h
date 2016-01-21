/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      GameStateManager.h
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        holds prototypes and variables of GamestateManager.c to be used in other files
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */

void GSM_Initialize(int InitLevel);
void GSM_Update(void);

void(*pLoad)(void);
void(*pInitialize)(void);
void(*pUpdate)(void);
void(*pDraw)(void);
void(*pFree)(void);
void(*pUnload)(void);

extern int Current;
extern int Previous;
extern int Next;