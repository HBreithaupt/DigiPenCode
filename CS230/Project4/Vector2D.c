/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : Vector2D.c
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : implementation of Vector2D.h
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#include "Vector2D.h"

#define EPSILON 0.0001
#define PI 3.141592653589793

////////////////////
// From Project 2 //
////////////////////

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = pVec0->x * -1;
	pResult->y = pVec0->y * -1;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;

}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float coefficient;
	float x0 = pVec0->x;
	float y0 = pVec0->y;
	
	coefficient = 1 / sqrt((x0 * x0) + (y0 * y0));

	pResult->x = coefficient * x0;
	pResult->y = coefficient * y0;
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c + pVec1->x;
	pResult->y = pVec0->y * c + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c - pVec1->x;
	pResult->y = pVec0->y * c - pVec1->y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	double length;
	double x0 = pVec0->x;
	double y0 = pVec0->y;

	length = sqrt(x0 * x0 + y0 * y0);

	return length;
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	double length;
	double x0 = pVec0->x;
	double y0 = pVec0->y;

	length = x0 * x0 + y0 * y0;

	return length;
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	double x0 = pVec0->x;
	double y0 = pVec0->y;

	double x1 = pVec1->x;
	double y1 = pVec1->y;

	double x2 = x0 - x1;
	double y2 = y0 - y1;

	double distance = sqrt(x2 * x2 + y2 * y2);

	return distance;
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{

	double x0 = pVec0->x;
	double y0 = pVec0->y;

	double x1 = pVec1->x;
	double y1 = pVec1->y;

	double x2 = x0 - x1;
	double y2 = y0 - y1;

	double distance = x2 * x2 + y2 * y2;

	return distance;
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{

	double x0 = pVec0->x;
	double y0 = pVec0->y;

	double x1 = pVec1->x;
	double y1 = pVec1->y;

	double product = x0 * x1 + y0 * y1;

	return product;
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle) * (180 / PI);
	pResult->y = sin(angle) * (180 / PI);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle);
	pResult->y = sin(angle);
}


// ---------------------------------------------------------------------------
