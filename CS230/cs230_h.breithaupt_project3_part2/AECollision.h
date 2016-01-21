//// ---------------------------------------------------------------------------
//// Project Name		:	Alpha Engine
//// File Name		:	AECollision.h
//// Author			:	Karim Fikani
//// Creation Date	:	2009/01/21
//// Purpose			:	header file for the collision module
//// History			:
//// - 2009/01/21		:	- initial implementation
//// ---------------------------------------------------------------------------
//
//#ifndef AE_COLLISION_H
//#define AE_COLLISION_H
//
////int		AECollisionResponse(AEGameObject *obj1, int id1, AEGameObject *obj2, int id2, float interTime, float t, float dt);
//
//// ---------------------------------------------------------------------------
//
//#ifdef __cplusplus
//
//extern "C"
//{
//#endif
//
//// ---------------------------------------------------------------------------
//
//AE_API int		AELineSegmentsIntersection(AEPoint2 pt1Start, AEPoint2 pt1End, AEVec2 pt1Vel, AEPoint2 pt2Start, AEPoint2 pt2End, AEVec2 pt2Norm, unsigned long colType, float *interTime, AEPoint2 *interPt, float t, float dt);
//AE_API int		AECircleLineSegmentIntersection(AEGameObject *circle, AEPoint2 ptStart, AEPoint2 ptEnd, AEVec2 norm, unsigned long colType, float *interTime, AEPoint2 *interPt, float t, float dt);
//AE_API int		AECircleCircleIntersection(AEGameObject *circle1, AEGameObject *circle2, float *interTime, AEPoint2 *interPt, float t, float dt);
//AE_API void		AECollisionResponse(AEGameObject *obj1, AEGameObject *obj2, AEPoint2 interPt, float interTime, float t, float dt);
//AE_API void		AEVec2Reflection(AEVec2* pResult, AEVec2* pVec0, AEVec2* pVec1);
//
//#ifdef __cplusplus 
//}
//#endif
//
//// ---------------------------------------------------------------------------
//
//#endif