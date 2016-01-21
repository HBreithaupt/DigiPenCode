/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      System.c
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        Notifies that the system application has started and when it ends
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */

#include "System.h"

FILE *output;
#pragma warning(disable: 4996)

void System_Initialize(void)
{
	output = fopen("output.txt", "w");
	fprintf(output, "System:Initialize\n");
}

void System_Exit(void)
{
	fprintf(output, "System:Exit");
	fclose(output);
}