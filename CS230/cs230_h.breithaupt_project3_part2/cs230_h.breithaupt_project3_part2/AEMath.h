// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEMath.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	main header file for the math library
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_MATH_H
#define AE_MATH_H

// ---------------------------------------------------------------------------

#include "AEVec2.h"
#include "AEMtx33.h"
#include "AELineSegment2.h"

#include <float.h>

#include "math.h"

// ---------------------------------------------------------------------------




// ---------------------------------------------------------------------------
#ifdef __cplusplus

extern "C"
{
#endif

//AE_API void MathInit();

// ---------------------------------------------------------------------------

AE_API f32 AEDegToRad(f32 x);
AE_API f32 AERadToDeg(f32 x);
/*
AE_API f32 AESin	(f32 x);
AE_API f32 AECos	(f32 x);
AE_API f32 AETan	(f32 x);
AE_API f32 AEASin	(f32 x);
AE_API f32 AEACos	(f32 x);
AE_API f32 AEATan	(f32 x);
*/
#define AESinDeg(x)		AESin(AEDegToRad(x))
#define AECosDeg(x)		AECos(AEDegToRad(x))
#define AETanDeg(x)		AETan(AEDegToRad(x))
#define AEASinDeg(x)	AERadToDeg(AEASin(x))
#define AEACosDeg(x)	AERadToDeg(AEACos(x))
#define AEATanDeg(x)	AERadToDeg(AEATan(x))

// ---------------------------------------------------------------------------

AE_API u32		AEIsPowOf2	(u32 x);
AE_API u32		AENextPowOf2(u32 x);
AE_API u32		AELogBase2	(u32 x);

AE_API f32		AEClamp		(f32 X, f32 Min, f32 Max);
AE_API f32		AEWrap		(f32 x, f32 x0, f32 x1);
AE_API f32		AEMin		(f32 x, f32 y);
AE_API f32		AEMax		(f32 x, f32 y);
AE_API int		AEInRange	(f32 x, f32 x0, f32 x1);

// ---------------------------------------------------------------------------

AE_API f32 AECalcDistPointToCircle		(AEVec2* pPos, AEVec2* pCtr, f32 radius);
AE_API f32 AECalcDistPointToRect		(AEVec2* pPos, AEVec2* pRect, f32 sizeX, f32 sizeY);
AE_API f32 AECalcDistPointToLineSeg		(AEVec2* pPos, AEVec2* pLine0, AEVec2* pLine1);
AE_API f32 AECalcDistPointToConvexPoly	(AEVec2* pPos, AEVec2* pVtx, u32 vtxNum);

AE_API f32 AECalcDistCircleToCircle		(AEVec2* pCtr0, f32 radius0, AEVec2* pCtr1, f32 radius1);
AE_API f32 AECalcDistCircleToRect		(AEVec2* pCtr0, f32 radius0, AEVec2* pRect0, f32 sizeX0, f32 sizeY0);
AE_API f32 AECalcDistCircleToLineSeg	(AEVec2* pPos, AEVec2* pLine0, AEVec2* pLine1);
AE_API f32 AECalcDistCircleToConvexPoly	(AEVec2* pPos, AEVec2* pVtx, u32 vtxNum);

AE_API f32 AECalcDistRectToRect			(AEVec2* pRect0, f32 sizeX0, f32 sizeY0, AEVec2* pRect1, f32 sizeX1, f32 sizeY1, AEVec2* pNormal);

// ---------------------------------------------------------------------------

AE_API int AETestPointToCircle			(AEVec2* pPos, AEVec2* pCtr, f32 radius);
AE_API int AETestPointToRect			(AEVec2* pPos, AEVec2* pRect, f32 sizeX, f32 sizeY);

AE_API int AETestCircleToCircle			(AEVec2* pCtr0, f32 radius0, AEVec2* pCtr1, f32 radius1);
AE_API int AETestCircleToRect			(AEVec2* pCtr0, f32 radius0, AEVec2* pRect0, f32 sizeX0, f32 sizeY0);

AE_API int AETestRectToRect				(AEVec2* pRect0, f32 sizeX0, f32 sizeY0, AEVec2* pRect1, f32 sizeX1, f32 sizeY1);

// ---------------------------------------------------------------------------





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

AE_API float AEStaticPointToStaticLineSegment(AEVec2 *P, AELineSegment2D *LS);





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
AE_API float AEAnimatedPointToStaticLineSegment(AEVec2 *Ps, AEVec2 *Pe, AELineSegment2D *LS, AEVec2 *Pi);




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
AE_API float AEAnimatedCircleToStaticLineSegment(AEVec2 *Ps, AEVec2 *Pe, float Radius, AELineSegment2D *LS, AEVec2 *Pi);



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
AE_API float AEReflectAnimatedPointOnStaticLineSegment(AEVec2 *Ps, AEVec2 *Pe, AELineSegment2D *LS, AEVec2 *Pi, AEVec2 *R);



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
AE_API float AEReflectAnimatedCircleOnStaticLineSegment(AEVec2 *Ps, AEVec2 *Pe, float Radius, AELineSegment2D *LS, AEVec2 *Pi, AEVec2 *R);



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
AE_API float AEAnimatedPointToStaticCircle(AEVec2 *Ps, AEVec2 *Pe, AEVec2 *Center, float Radius, AEVec2 *Pi);


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
AE_API float AEReflectAnimatedPointOnStaticCircle(AEVec2 *Ps, AEVec2 *Pe, AEVec2 *Center, float Radius, AEVec2 *Pi, AEVec2 *R);



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
AE_API float AEAnimatedCircleToStaticCircle(AEVec2 *Center0s, AEVec2 *Center0e, float Radius0, AEVec2 *Center1, float Radius1, AEVec2 *Pi);


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
AE_API float AEReflectAnimatedCircleOnStaticCircle(AEVec2 *Center0s, AEVec2 *Center0e, float Radius0, AEVec2 *Center1, float Radius1, AEVec2 *Pi, AEVec2 *R);



/*
// sweep a circle with radius 'radius' from ctr0 -> ctr1 againts a point
// * return -ve if circle does not touch the point at any time
AE_API f32 AESweepCircleToPoint	(AEVec2* pCtr0, AEVec2* pCtr1, f32 radius, AEVec2* pP);

// sweep a circle with radius 'radius' from ctr0 -> ctr1 againts a line segment
// * return -ve if circle does not intersect the line segment at any time
AE_API f32 AESweepCircleToLineSeg	(AEVec2* pCtr0, AEVec2* pCtr1, f32 radius, AEVec2* pP0, AEVec2* pP1, AEVec2* pN);


//TO TEST
//Sweeps a moving point against a static line
AE_API f32 AESweepPointToLine		(AEVec2 *pPos, AEVec2 *pVel, AEVec2 *pPnt, AEVec2 *pDirection);

//TO TEST
//Sweeps a moving circle against a static line
AE_API f32 AESweepCircleToLine		(AEVec2 *pCtr, f32 radius, AEVec2 *pVel, AEVec2 *pPnt, AEVec2 *pDirection);

//TO TEST
//Reflects a moving point on a static line. Returns 0 if there is no
//collision between the point and the line.
AE_API int AEReflectPointOnLine	(AEVec2 *pPos, AEVec2 *pVel, AEVec2 *pPnt, AEVec2 *pDirection, AEVec2 *pNewPosition, AEVec2 *pNewVelocity);


//TO TEST
//Reflects a moving circle on a static line. Returns 0 if there is no
//collision between the circle and the line.
AE_API int AEReflectCircleOnLine	(AEVec2 *pCtr, f32 radius, AEVec2 *pVel, AEVec2 *pPnt, AEVec2 *pDirection, AEVec2 *pNewPosition, AEVec2 *newVelocity);
*/
// ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // AE_MATH_H
