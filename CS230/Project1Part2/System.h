/*-------------------------------------------------------------------------- -
Project Title :  CS230 Project 1, Part 1
File Name :      System.h
Author :         Haven Breithaupt
Creation Date :  January 19, 2015
Purpose :        contains function protypes and file pointer of System.c to be used in other files
History
- 1/19/2015 created and completed

© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
---------------------------------------------------------------------------- */
#include <stdio.h>

extern FILE *output;

void System_Initialize(void);
void System_Exit(void);