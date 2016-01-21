// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEVec2.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	header file for the 2D vector library
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_VEC2_H
#define AE_VEC2_H

#include "AEExport.h"
#include "AETypes.h"

// ---------------------------------------------------------------------------

//AE_API typedef struct AEVec2
typedef struct AEVec2
{
	f32 x, y;
}AEVec2;

// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif


AE_API int	AEVec2Test				(int i1, int i2);


AE_API void	AEVec2Zero				(AEVec2* pResult);
AE_API void	AEVec2Set				(AEVec2* pResult, f32 x, f32 y);

AE_API void	AEVec2Neg				(AEVec2* pResult, AEVec2* pVec0);
AE_API void	AEVec2Add				(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1);
AE_API void	AEVec2Sub				(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1);
AE_API void	AEVec2Normalize			(AEVec2* pResult, AEVec2* pVec0);

AE_API void	AEVec2Scale				(AEVec2* pResult, AEVec2* pVec0, f32 c);
AE_API void	AEVec2ScaleAdd			(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1, f32 s);
AE_API void	AEVec2ScaleSub			(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1, f32 s);

AE_API void	AEVec2Project			(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1);
AE_API void	AEVec2ProjectPerp		(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1);

AE_API void	AEVec2Lerp				(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1, f32 t);

AE_API f32		AEVec2Length			(AEVec2* pVec0);
AE_API f32		AEVec2SquareLength		(AEVec2* pVec0);
AE_API f32		AEVec2Distance			(AEVec2* pVec0, AEVec2* pVec1);
AE_API f32		AEVec2SquareDistance	(AEVec2* pVec0, AEVec2* pVec1);

AE_API f32		AEVec2DotProduct		(AEVec2* pVec0, AEVec2* pVec1);
AE_API f32		AEVec2CrossProductMag	(AEVec2* pVec0, AEVec2* pVec1);

AE_API void		AEVec2FromAngle(AEVec2* pResult, f32 angle);



#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // VEC2_H