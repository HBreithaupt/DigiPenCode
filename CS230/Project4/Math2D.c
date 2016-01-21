/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : Math2D.c
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : implementayion of math.h
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#include "Math2D.h"
#include "stdio.h"
#include "Vector2D.h"

////////////////////////
// From Project 2 & 3 //
////////////////////////


/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	
	if (Vector2DDistance(pP, pCenter) <           Radius)
		return 1;
	else 
		return 0;;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	/* if point is to the left of rectangle*/
	if (pPos->x <= pRect->x)
		if (Vector2DSquareDistance(pPos, pRect) < Width * Width)
			return 1;

	/* if point is to the right of triangle */
	if (pPos->x >= pRect->y)
		if (Vector2DSquareDistance(pPos, pRect) < Width * Width)
			return 1;

	/* if point is above the rectangle */
	if (pPos->y >= pRect->y)
		if (Vector2DSquareDistance(pPos, pRect) < Height * Height)
			return 1;

	/* if point is beloe the rectangle*/
	if (pPos->y <= pRect->y)
		if (Vector2DSquareDistance(pPos, pRect) < Height * Height)
			return 1;

  return 0;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{

	/* colliding (including touching ) */
	if (Vector2DDistance(pCenter0, pCenter1) <= Radius0 + Radius1)
		return 1;


  return 0;}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{


	/* rect0 if left of rect1*/
	if (pRect0->x  <= pRect1->x)
		if (Vector2DDistance(pRect0, pRect1) <= Width0 + Width1)
			return 1;

	/* rect0 is right of rect1*/
	if (pRect0->x >= pRect1->x)
		if (Vector2DDistance(pRect0, pRect1) <= Width0 + Width1)
			return 1;

	/* rect0 is above rect1*/
	if (pRect0->y >= pRect1->y)
		if (Vector2DDistance(pRect0, pRect1) <= Height0 + Height1)
			return 1;

	/* rect0 is below rect1 */
	if (pRect0->y <= pRect1->y)
		if (Vector2DDistance(pRect0, pRect1) <= Height0 + Height1)
			return 1;

  return 0;}

/*
This function checks if a static circle is intersecting with a static rectangle

Circle:		Center is "Center", radius is "Radius"
Rectangle:	Center is "Rect", width is "Width" and height is "Height"
Function returns true is the circle and rectangle are intersecting, otherwise it returns false
*/

int StaticCircleToStaticRectangle(Vector2D *pCenter, float Radius, Vector2D *pRect, float Width, float Height)
{
	
	Vector2D snapped = { 0 };

	if (pCenter->x > pRect->x - Width /2)
		snapped.x = pRect->x - Width / 2;
	else if (pCenter->x < pRect->x + Width / 2)
		snapped.x = pRect->x + Width / 2;

	if (pCenter->y > pRect->y + Height / 2)
		snapped.y = pRect->y + Height / 2;
	else if (pCenter->y > pRect->y - Height / 2)
		snapped.y = pRect->y - Height / 2;

	return StaticPointToStaticCircle(&snapped, pCenter, Radius);


}

//////////////////////
// New to project 4 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	return Vector2DDotProduct(&P, &LS->mN) - LS->mNdotP0;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D PsPe, PiP0, P1P0, PiP1, P0P1;

	Vector2DSub(&PsPe, Pe, Ps);

	float t = (LS->mNdotP0 - Vector2DDotProduct(&LS->mN, Ps)) / Vector2DDotProduct(&PsPe, &LS->mN);

	if (t < 0 || t > 1)
		return -1.0f;

	Vector2DScaleAdd(Pi, &PsPe, Ps, t);

	Vector2DSub(&PiP0, Pi, &LS->mP0);
	Vector2DSub(&P1P0, &LS->mP1, &LS->mP0);

	Vector2DSub(&PiP1, Pi, &LS->mP1);
	Vector2DSub(&P0P1, &LS->mP0, &LS->mP1);

	if (Vector2DDotProduct(&PiP0, &P1P0) < 0)
		return -1.0f;

	if (Vector2DDotProduct(&PiP1, &P0P1) < 0)
		return -1.0f;

	return t;
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	float t, d;

	Vector2D PsPe;

	Vector2D P1P0;
	Vector2D P0P1;

	Vector2D P0Pi;
	Vector2D P1Pi;

	Vector2DSub(&P0P1, &LS->mP1, &LS->mP0);
	Vector2DSub(&P1P0, &LS->mP0, &LS->mP1);


	/* vector of the line segment */
	Vector2DSub(&PsPe, Pe, Ps);

	/* tests for non collision */

	if (StaticPointToStaticLineSegment(Ps, LS) < -Radius &&
		StaticPointToStaticLineSegment(Pe, LS) < -Radius)
	{
		return -1.0f;
	}

	if (StaticPointToStaticLineSegment(Ps, LS) > Radius &&
		StaticPointToStaticLineSegment(Pe, LS) > Radius)
	{
		return -1.0f;
	}

	/* possible collision, calculate t */

	if (StaticPointToStaticLineSegment(Ps, LS) < -Radius)
		d = -Radius;
	else
		d = -Radius;

	t = (LS->mNdotP0 - Vector2DDotProduct(&LS->mN, Ps) + d) / Vector2DDotProduct(&LS->mN, &PsPe);

	/* bounds check t */
	if (t < 0 || t > 1)
		return -1.0f;


	/* calculate possible collision point */

	Vector2DScaleAdd(Pi, &PsPe, Ps, t);

	Vector2DSub(&P0Pi, Pi, &LS->mP0);
	Vector2DSub(&P1Pi, Pi, &LS->mP1);

	/* final non-collision test */
	if (Vector2DDotProduct(&P0Pi, &P0P1) < 0)
		return -1.0f;

	if (Vector2DDotProduct(&P1Pi, &P1P0) < 0)
		return -1.0f;

	/* return time of intersection */
	return t;

}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	float check = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);

	if (check == -1.0f)
		return -1.0f;

	Vector2D i, s;

	Vector2DSub(&i, Pe, Pi);

	Vector2DScale(&s, &LS->mN, Vector2DDotProduct(&i, &LS->mN));

	Vector2DScale(&s, &s, 2.0);

	Vector2DSub(R, &i, &s);

	return check;
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	LineSegment2D Shifted;

	Shifted.mP0 = LS->mP0;
	Shifted.mP1 = LS->mP1;
	Shifted.mN = LS->mN;
	Shifted.mNdotP0 = LS->mNdotP0;

	if (StaticPointToStaticLineSegment(Ps, LS) < -Radius)
		Shifted.mNdotP0 -= Radius;
	else
		Shifted.mNdotP0 += Radius;

	float check = AnimatedPointToStaticLineSegment(Ps, Pe, &Shifted, Pi);

	if (check < 0 || check > 1)
		return -1.0f;

	float reflected = ReflectAnimatedPointOnStaticLineSegment(Ps, Pe, &Shifted, Pi, R);

	return reflected;

	
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	return 0;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	return 0;
}



/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	return 0;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	return 0;
}
