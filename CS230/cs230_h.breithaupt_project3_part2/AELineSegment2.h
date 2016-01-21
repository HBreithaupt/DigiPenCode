// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AELineSegment2.h
// Author			:	Antoine Abi Chacra
// Creation Date	:	2012/03/19
// Purpose			:	header file for the 2D line segment library
// History			:
// ---------------------------------------------------------------------------

#ifndef AE_LS2_H
#define AE_LS2_H

// ---------------------------------------------------------------------------


typedef struct AELineSegment2D
{
	AEVec2 mP0;		// Point on the line
	AEVec2 mP1;		// Point on the line
	AEVec2 mN;		// Line's normal
	float mNdotP0;		// To avoid computing it every time it's needed
}AELineSegment2D;


// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif




/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line
*/
AE_API int AEBuildLineSegment2D(AELineSegment2D *LS, AEVec2 *Point0, AEVec2 *Point1);




#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // VEC2_H