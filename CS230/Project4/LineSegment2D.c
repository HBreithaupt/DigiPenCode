/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : LineSegment2D.c
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : implementation of LineSegment2D.h
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#include "LineSegment2D.h"


int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{

	/* both points are the same so dont build a line segment*/
	if ((Point0->x == Point1->x) && (Point0->y == Point1->y))
		return 0;

	/* build vector from the two points */
	Vector2D Segment;

	Segment.x = Point1->x - Point0->x;
	Segment.y = Point1->y - Point0->y;

	/* assign end points of the segment */

	LS->mP0.x = Point0->x;
	LS->mP0.y = Point0->y;

	LS->mP1.x = Point1->x;
	LS->mP1.y = Point1->y;

	/* calculate normal to the line being built */
	LS->mN.x =  Segment.y;
	LS->mN.y = -Segment.x;

	/* normalize normal vector */
	Vector2DNormalize(&LS->mN, &LS->mN);

	/* calc normal dot point0 */
	LS->mNdotP0 = LS->mN.x * LS->mP0.x + LS->mN.y * LS->mP0.y;

	/* return 1 for successful line segment */
	return 1;
}