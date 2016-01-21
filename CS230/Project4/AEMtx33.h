// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEMtx33.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	header file for the 3x3 matrix library
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_MTX33_H
#define AE_MTX33_H

// ---------------------------------------------------------------------------
// Defines

#define AEMtx33RowCol(pMtx, row, col) (pMtx)->m[(row)][(col)]



// ---------------------------------------------------------------------------
// Struct/Class definitions

// matrix is stored in column major format (ie. the translation term is in the right most column)

typedef struct AEMtx33
{
	f32	m[3][3];
}AEMtx33;

// ---------------------------------------------------------------------------

#ifdef __cplusplus 
extern "C"
{
#endif

// ---------------------------------------------------------------------------

AE_API void 		AEMtx33Identity				(AEMtx33* pResult);

AE_API void 		AEMtx33Transpose			(AEMtx33* pResult, AEMtx33* pMtx);
AE_API f32			AEMtx33Inverse				(AEMtx33* pResult, AEMtx33* pMtx);
AE_API void 		AEMtx33InvTranspose			(AEMtx33* pResult, AEMtx33* pMtx);

AE_API void 		AEMtx33Concat				(AEMtx33* pResult, AEMtx33* pMtx0, AEMtx33* pMtx1);

AE_API void 		AEMtx33Orthogonalize		(AEMtx33* pResult, AEMtx33* pMtx);

AE_API f32			AEMtx33Determinant			(AEMtx33* pMtx);

// ---------------------------------------------------------------------------

AE_API void 		AEMtx33SetCol				(AEMtx33* pResult, u32 col,  AEVec2* pVec);
AE_API void 		AEMtx33SetRow				(AEMtx33* pResult, u32 row,  AEVec2* pVec);
AE_API void 		AEMtx33GetCol				(AEVec2*  pResult, u32 col,  AEMtx33* pMtx);
AE_API void			AEMtx33GetRow				(AEVec2*  pResult, u32 row,  AEMtx33* pMtx);

// ---------------------------------------------------------------------------

AE_API void 		AEMtx33Trans				(AEMtx33* pResult, f32 x, f32 y);
AE_API void 		AEMtx33TransApply			(AEMtx33* pResult, AEMtx33* pMtx, f32 x, f32 y);

AE_API void 		AEMtx33Scale				(AEMtx33* pResult, f32 x, f32 y);
AE_API void 		AEMtx33ScaleApply			(AEMtx33* pResult, AEMtx33* pMtx, f32 x, f32 y);

AE_API void 		AEMtx33Rot					(AEMtx33* pResult, f32 angle);
AE_API void 		AEMtx33RotDeg				(AEMtx33* pResult, f32 angle);

AE_API void			AEMtx33BuildFullTransform	(AEMtx33* pResult, float posX, float posY, float angleDeg, float scaleX, float scaleY);

// ---------------------------------------------------------------------------

AE_API void 		AEMtx33MultVec				(AEVec2* pResult, AEMtx33* pMtx, AEVec2* pVec);
AE_API void 		AEMtx33MultVecArray			(AEVec2* pResult, AEMtx33* pMtx, AEVec2* pVec, u32 count);
AE_API void 		AEMtx33MultVecSR			(AEVec2* pResult, AEMtx33* pMtx, AEVec2* pVec);
AE_API void 		AEMtx33MultVecArraySR		(AEVec2* pResult, AEMtx33* pMtx, AEVec2* pVec, u32 count);
	
// ---------------------------------------------------------------------------




#ifdef __cplusplus 
}
#endif

#endif // MTX_H