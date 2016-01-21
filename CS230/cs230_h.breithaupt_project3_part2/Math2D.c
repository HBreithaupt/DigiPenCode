#include "Math2D.h"
#include "stdio.h"

////////////////////
// From Project 2 //
////////////////////


/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if (Vector2DDistance(pP, pCenter) < Radius)
		return 1;
	else 
		return 0;
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


  return 0;
}

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

  return 0;
}

//////////////////////
// New to Project 3 //
//////////////////////

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