/*---------------------------------------------------------------------------
Project Title : Project2Part1
File Name : CS230_Project2_SmokeTest.c
Author : Haven Breithaupt
Creation Date: n/a
Purpose : this file is a driver to test functions implemented in math2d.c, matrix2d.c and vector2d.c
History
 given as template to complete project
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Math2D.h"
#include "Matrix2D.h"

#define EPSILON 0.0001f
#define PI      3.1415926535897932384626433832795

//
void PrintVector(char *txt, Vector2D *pVec0)
{
	printf("%s:\t%f, %f\n", txt, pVec0->x, pVec0->y);
}

float CompareVector2D(Vector2D *pSrc, Vector2D *pDst)
{
	float d = 0.0f;

	d += fabs(pSrc->x - pDst->x);
	d += fabs(pSrc->y - pDst->y);

	return d;
};

float CompareMatrix2D(Matrix2D* pSrc, Matrix2D* pDst)
{
	long i, j;
	float d = 0.0f;

	for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
			d += fabs(pSrc->m[j][i] - pDst->m[j][i]);

	return d;
}

int main()
{
	Vector2D v1, v2, v3, result;
	float scale;
	Matrix2D id, m0, m1;
	Vector2D  u;
	float d, x, y;
	long  n;
	long i, j;
	float radius;

	v1.x = v1.y = 7.0f;
	Vector2DZero(&v1);
	result.x = result.y = 0.0f;
	printf("Vector2DZero: %s\n", (CompareVector2D(&result, &v1) < EPSILON) ? "Pass" : "Fail");


	Vector2DSet(&v1, 1.0f, 2.0f);
	result.x = 1.0f;	result.y = 2.0f;
	printf("Vector2DSet: %s\n", (CompareVector2D(&result, &v1) < EPSILON) ? "Pass" : "Fail");


	v1.x = 2.0f; v1.y = -4.0f;
	Vector2DNeg(&v2, &v1);
	result.x = -2.0f;	result.y = 4.0f;
	printf("Vector2DNeg: %s\n", (CompareVector2D(&result, &v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	Vector2DAdd(&v3, &v1, &v2);
	result.x = result.y = 3.0f;
	printf("Vector2DAdd: %s\n", (CompareVector2D(&result, &v3) < EPSILON) ? "Pass" : "Fail");


	v1.x = 2.0f; v1.y = -4.0f;
	v2.x = 1.0f; v2.y = 7.0f;
	Vector2DSub(&v3, &v1, &v2);
	result.x = 1.0f;	result.y = -11.0f;
	printf("Vector2DSub: %s\n", (CompareVector2D(&result, &v3) < EPSILON) ? "Pass" : "Fail");


	v1.x = 3.0f; v1.y = 4.0f;
	Vector2DNormalize(&v2, &v1);
	result.x = 0.6f;	result.y = 0.8f;
	printf("Vector2DNormalize: %s\n", (CompareVector2D(&result, &v2) < EPSILON) ? "Pass" : "Fail");


	v1.x = 2.0f; v1.y = -5.0f;
	Vector2DScale(&v2, &v1, 3.0f);
	result.x = 6.0f;	result.y = -15.0f;
	printf("Vector2DScale: %s\n", (CompareVector2D(&result, &v2) < EPSILON) ? "Pass" : "Fail");

	v1.x = 2.0f; v1.y = -5.0f;
	v2.x = 6.0f; v2.y =  2.0f;
	scale = 3.0f;
	Vector2DScaleAdd(&v3, &v1, &v2, scale);
	result.x = 12.0f; result.y = -13.0f;
	printf("Vector2DScaleAdd: %s\n", (CompareVector2D(&result, &v3) < EPSILON) ? "Pass" : "Fail");

	Vector2DScaleSub(&v3, &v1, &v2, scale);
	result.x = 0.f; result.y = -17.f;
	printf("Vector2DScaleSub: %s\n", (CompareVector2D(&result, &v3) < EPSILON) ? "Pass" : "Fail");

	v1.x = 3.0f; v1.y = -4.0f;
	printf("Vector2DLength: %s\n", (fabs(Vector2DLength(&v1) - 5.0f)  < EPSILON) ? "Pass" : "Fail");


	v1.x = 3.0f; v1.y = -4.0f;
	printf("Vector2DSquareLength: %s\n", (fabs(Vector2DSquareLength(&v1) - 25.0f)  < EPSILON) ? "Pass" : "Fail");


	v1.x = 2.0f;	v1.y = 3.0f;
	v2.x = 4.0f;	v2.y = -1.0f;
	printf("Vector2DDistance: %s\n", (fabs(Vector2DDistance(&v1, &v2) - 4.472136)  < EPSILON) ? "Pass" : "Fail");


	v1.x = 2.0f;	v1.y = 3.0f;
	v2.x = 4.0f;	v2.y = -1.0f;
	printf("Vector2DSquareDistance: %s\n", (fabs(Vector2DSquareDistance(&v1, &v2) - 20.0f)  < EPSILON) ? "Pass" : "Fail");


	v1.x = 3.0f;	v1.y = 2.0f;
	v2.x = 4.0f;	v2.y = -6.0f;
	printf("Vector2DDotProduct: %s\n", (fabs(Vector2DDotProduct(&v1, &v2)) < EPSILON) ? "Pass" : "Fail");


	printf("\n------Testing StaticPointToStaticCircle------\n\n");
	v1.x = 10.f; v1.y = 10.f;
	v2.x = 11.4f; v2.y = 11.4f;
	radius = 2.f;
	printf("StaticPointToStaticCircle Collision: %s\n", (StaticPointToStaticCircle(&v2, &v1, radius)) ? "Pass" : "Fail" );

	v2.x = 12.f; v2.y = 12.f;
	printf("StaticPointToStaticCircle Non Collision: %s\n", (!StaticPointToStaticCircle(&v2, &v1, radius)) ? "Pass" : "Fail" );



	printf("\n------Running Matrix Tests------\n\n");



	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	// ====================
	// test Matrix2DIdentity
	// ====================

	Matrix2DIdentity(&m0);
	d = CompareMatrix2D(&id, &m0);
	printf("Matrix2DIdentity : %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// ====================
	// test Matrix2DTrans
	// ====================

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	Matrix2DTranslate(&m0, x, y);
	m0.m[0][2] -= x;
	m0.m[1][2] -= y;
	printf("Matrix2DTranslate: %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// ====================
	// test Matrix2DScale
	// ====================

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	Matrix2DScale(&m0, x, y);
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	printf("Matrix2DScale    : %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// ====================
	// test Matrix2DConcat
	// ====================

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	Matrix2DTranslate (&m0, x, y);
	Matrix2DScale (&m1, x, y);
	Matrix2DConcat(&m0, &m0, &m1);
	m0.m[0][2] -= x;
	m0.m[1][2] -= y;
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	printf("Matrix2DConcat 1 : %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	Matrix2DTranslate (&m0, x, y);
	Matrix2DScale (&m1, x, y);
	Matrix2DConcat(&m0, &m1, &m0);
	m0.m[0][2] -= x * x;
	m0.m[1][2] -= y * y;
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	printf("Matrix2DConcat 2 : %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// ====================
	// test Matrix2DRotRad
	// ====================

	n = (rand() % 16) + 15;
	Matrix2DIdentity(&m0);
	Matrix2DRotRad  (&m1, 2.0f * PI / n);

	for (i = 0; i < n; i++)
		Matrix2DConcat(&m0, &m1, &m0);

	printf("Matrix2DRotRad   : %s (%d)\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail", n);

	// ====================
	// test Matrix2DRotDeg
	// ====================

	n = (rand() % 16) + 15;
	Matrix2DIdentity(&m0);
	Matrix2DRotDeg  (&m1, 360.0f / n);

	for (i = 0; i < n; i++)
		Matrix2DConcat(&m0, &m1, &m0);

	printf("Matrix2DRotDeg   : %s (%d)\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail", n);

	// ====================
	// test Matrix2DTranspose
	// ====================

	Matrix2DRotRad   (&m0, rand() / (float)(RAND_MAX) * 2.0f * PI);
	Matrix2DTranspose(&m1, &m0);
	Matrix2DConcat   (&m0, &m1, &m0);

	printf("Matrix2DTranspose: %s\n", (CompareMatrix2D(&id, &m0) < EPSILON) ? "Pass" : "Fail");

	// ====================
	// test Matrix2DMultVec
	// ====================

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	n = (rand() % 16) + 15;
	Vector2DSet		(&u, x, y);
	Matrix2DRotRad	(&m0, 2.0f * PI / n);

	for (i = 0; i < n; i++)
		Matrix2DMultVec(&u, &m0, &u);

	printf("Matrix2DMultVec  : %s\n", ((fabs(u.x - x) + fabs(u.y - y)) < EPSILON) ? "Pass" : "Fail");

	// generate 2 random numbers
	x = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX) - 1.0f;

	n = (rand() % 16) + 15;
	Vector2DSet		(&u, x, y);
	Matrix2DTranslate	(&m0, x, y);

	for (i = 1; i < n; i++)
		Matrix2DMultVec(&u, &m0, &u);

	printf("Matrix2DMultVec  : %s\n", ((fabs(u.x - x * n) + fabs(u.y - y * n)) < EPSILON) ? "Pass" : "Fail");

	printf("\n------Testing New Collision Functions------\n\n");

	//StaticPointToStaticRect
	Vector2DSet(&v1, 1.f, 1.f); //point
	Vector2DSet(&v2, 0.f, 0.f); //rect
	printf("StaticPointToStaticRect Collision: %s\n", (StaticPointToStaticRect(&v1, &v2, 2.f, 2.f) ? "Pass" : "Fail"));
	printf("StaticPointToStaticRect Non Collision: %s\n\n", (!StaticPointToStaticRect(&v1, &v2, 1.f, 1.f) ? "Pass" : "Fail"));

	//StaticCircleToStaticCircle
	Vector2DSet(&v1, 2.f, 0.f);
	printf("StaticCircleToStaticCircle Collision Touch: %s\n", (StaticCircleToStaticCircle(&v1, 1.f, &v2, 1.f) ? "Pass" : "Fail"));
	printf("StaticCircleToStaticCircle Collision: %s\n", (StaticCircleToStaticCircle(&v1, 2.f, &v2, 1.f) ? "Pass" : "Fail"));
	printf("StaticCircleToStaticCircle Non Collision: %s\n\n", (!StaticCircleToStaticCircle(&v1, 0.5f, &v2, 1.f) ? "Pass" : "Fail"));

	//StaticRectToStaticRect
	Vector2DSet(&v1, 2.f, 2.f);
	printf("StaticRectToStaticRect Non Collision: %s\n", (!StaticRectToStaticRect(&v1, 1.f, 1.f, &v2, 1.f, 1.f) ? "Pass" : "Fail"));
	printf("StaticRectToStaticRect Collision Touch: %s\n", (StaticRectToStaticRect(&v1, 2.f, 2.f, &v2, 2.f, 2.f) ? "Pass" : "Fail"));
	printf("StaticRectToStaticRect Collision Intersect: %s\n", (StaticRectToStaticRect(&v1, 3.f, 3.f, &v2, 3.f, 3.f) ? "Pass" : "Fail"));

	return 1;
}
