/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : Linesegment2D.h
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : function prototypes of Linesegment2D.c
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#ifndef LINESEGMENT2D_H
#define LINESEGMENT2D_H

#include "Vector2D.h"



typedef struct LineSegment2D
{
	Vector2D mP0;		// Point on the line
	Vector2D mP1;		// Point on the line
	Vector2D mN;		// Line's normal
	float mNdotP0;		// To avoid computing it every time it's needed
}LineSegment2D;


/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line

 - Returns 1 if the line equation was built successfully 
*/
int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1);




#endif