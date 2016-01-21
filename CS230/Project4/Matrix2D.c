/*---------------------------------------------------------------------------
Project Title : Project4Part1
File Name : Matrix2D.c
Author : Haven Breithaupt
Creation Date : 3/27/2015
Purpose : implementation of Matrix2D.h
History
3/27/2105 - created and completed
© Copyright 1996 - 2015, DigiPen Institute of Technology(USA).All rights reserved.
----------------------------------------------------------------------------*/
#include "Matrix2D.h"

#define PI 3.141592653589793


////////////////////
// From project 2 //
////////////////////

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
    pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;

	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = 0;
	
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
    pResult->m[0][0] = pMtx->m[0][0];
	pResult->m[0][1] = pMtx->m[1][0];
	pResult->m[0][2] = pMtx->m[2][0];

	pResult->m[1][0] = pMtx->m[0][1];
	pResult->m[1][1] = pMtx->m[1][1];
	pResult->m[1][2] = pMtx->m[2][1];
	
	pResult->m[2][0] = pMtx->m[0][2];
	pResult->m[2][1] = pMtx->m[1][2];
	pResult->m[2][2] = pMtx->m[2][2];

}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
  
	Matrix2D Result = { 0 };

	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
			for (int k = 0; k <= 2; k++)
				Result.m[i][j] += pMtx0->m[i][k] * pMtx1->m[k][j];

	for (int row = 0; row <= 2; row++)
		for (int column = 0; column <= 2; column++)
			pResult->m[row][column] = Result.m[row][column];

}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x *p y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
  
	Matrix2DIdentity(pResult);

	pResult->m[0][2] = x;
	pResult->m[1][2] = y;

}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x *p y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
    Matrix2DIdentity(pResult);

	pResult->m[0][0] = x;
	pResult->m[1][1] = y;

}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
  	Matrix2DIdentity(pResult);

	double angle_convert = Angle * (PI / 180);

	double cos_angle = cos(angle_convert);
	double sin_angle = sin(angle_convert);

	pResult->m[0][0] = cos_angle;
	pResult->m[0][1] = -sin_angle;
	pResult->m[1][0] = sin_angle;
	pResult->m[1][1] = cos_angle;


}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
    float cos_angle = cos(Angle);
	float sin_angle = sin(Angle);

	pResult->m[0][0] = cos_angle;
	pResult->m[0][1] = -sin_angle;
	pResult->m[0][2] = 0;

	pResult->m[1][0] = sin_angle;
	pResult->m[1][1] = cos_angle;
	pResult->m[1][2] = 0;

	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;

}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
  
	Matrix2D VectorResult = { 0 };
	Matrix2D *pVector = &VectorResult;

	Matrix2DIdentity(pVector);

	VectorResult.m[0][2] = pVec->x;
	VectorResult.m[1][2] = pVec->y;

	Matrix2DConcat(pVector, pMtx, pVector);

	pResult->x = VectorResult.m[0][2];
	pResult->y = VectorResult.m[1][2];
}

// ---------------------------------------------------------------------------
