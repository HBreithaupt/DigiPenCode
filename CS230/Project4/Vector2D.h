/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : Vector2D.h
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : function prototypes of Vector2D.c
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#ifndef VECTOR2_H
#define VECTOR2_H

#include "math.h"



typedef struct Vector2D
{
	float x, y;
}Vector2D;

////////////////////////
// From Project 2 & 3 //
////////////////////////


void Vector2DZero(Vector2D *pResult);

void Vector2DSet(Vector2D *pResult, float x, float y);

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0);

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0);

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c);

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

float Vector2DLength(Vector2D *pVec0);

float Vector2DSquareLength(Vector2D *pVec0);

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1);

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1);

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1);

void Vector2DFromAngle(Vector2D *pResult, float angle);


#endif