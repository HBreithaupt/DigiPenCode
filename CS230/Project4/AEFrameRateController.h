// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEFrameRateController.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2007/04/26
// Purpose			:	header file for the frame rate controller
// History			:
// - 2007/04/26		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_FRAME_RATE_CONTROLLER_H
#define AE_FRAME_RATE_CONTROLLER_H

// ---------------------------------------------------------------------------
// Externs

// ---------------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------------

#ifdef __cplusplus

extern "C"
{
#endif



// ---------------------------------------------------------------------------
#if(EXPORT_WINDOWS == 1)
// Frame management
/****************************************************************************/
/*/Ignore these functions, they are used internally by AE to handle frames./*/
/****************************************************************************/
/****/AE_API void	AEFrameRateControllerInit	(unsigned int FrameRateMax);/****/
/****/AE_API void	AEFrameRateControllerReset	();                       /****/
/****/AE_API void	AEFrameRateControllerStart	();                       /****/
/****/AE_API void	AEFrameRateControllerEnd	();                         /****/
/****************************************************************************/

/**
 * @brief Gets the frame time from Alpha Engine.
 * @details Use this to make sure things such as movement and physics happen at a
 * consistent speed across multiple devices or framerates. It should be used to set a
 * dt variable for use in physics and other time-sensitive calculations and computations.
 * @return The time between the start of the previous frame and the start of the current frame.
 */
AE_API f64 AEFrameRateControllerGetFrameTime();
/**
 * @brief Gets the number of frames that have elapsed since the engine started running.
 * @return Returns the total frames that have elapsed.
 */
AE_API u32 AEFrameRateControllerGetFrameCount();
#endif
// ---------------------------------------------------------------------------



#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // AE_FRAME_RATE_CONTROLLER_H

