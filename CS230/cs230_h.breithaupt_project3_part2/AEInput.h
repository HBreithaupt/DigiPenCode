// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEInput.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	declaration for input stuff
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_INPUT_H
#define AE_INPUT_H

// ---------------------------------------------------------------------------
// Defines/Enums

// ---------------------------------------------------------------------------
// Externs

// ---------------------------------------------------------------------------
// class definitions

// ---------------------------------------------------------------------------
// Function prototypes

// ---------------------------------------------------------------------------

#ifdef __cplusplus

extern "C"
{
#endif

// ---------------------------------------------------------------------------

#if(EXPORT_WINDOWS == 1)
AE_API int AEInputInit();
AE_API void AEInputReset();
/**
* @brief Updates the input information inside the input system.
* @details This function should be called every frame or game loop.
* Any new input information is stored to be accessed by the other
* input system function calls.
*/
AE_API void AEInputUpdate();
AE_API void AEInputExit();

/**
* @brief Checks the current status of a key.
* @details Checks to see if the specified key is currently pressed or not.
*
* @param[in] key The input status for this key will be checked.
* @return Whether the key is currently pressed or not.
*/
AE_API u8 AEInputCheckCurr		(u8 key);
/**
* @brief Checks the last status of a key.
* @details Checks to see if the specified key was pressed before the most
* recent call to AEInputUpdate().
*
* @param[in] key The previous input status for this key will be checked.
* @return Whether the key was pressed or not before the last update call.
*/
AE_API u8 AEInputCheckPrev		(u8 key);
/**
* @brief Checks if a key was initially pressed during the latest update.
* @details Determines if a key was triggered in the latest AEInputUpdate.
* A key is considered 'Triggered' if and only if it
* was not pressed in the previous call to AEInputUpdate(), and was pressed for  
* the most recent call to AEInputUpdate().
*
* @param[in] key Specifies which key to check for 'Triggered' status.
* @return Whether the key was triggered in the last AEInputUpdate() call or not.
*/
AE_API u8 AEInputCheckTriggered (u8 key);
/**
* @brief Checks if a key was released during the latest update.
* @details Determines if a key was released during the last call to AEInputUpdate().
* 'Released' is when a key is not pressed in the latest AEInputUpdate() call, 
* but was pressed during the previous call.
*
* @param[in] key Specifies which key to check for 'Released' status.
* @return Whether the key was released in the last AEInputUpdate() call or not.
*/
AE_API u8 AEInputCheckReleased	(u8 key);

/**
* @brief Gets the current cursor position in window coordinates.
* @details Gets the cursor position in the window. The origin of the window is
* located in the top left corner, and the Y-axis is inverted. The lower in the 
* window the higher the Y-coordinate goes.
*
* @param[in,out] pX Pointer to where the mouse X position will be stored.
* @param[in,out] pY Pointer to where the mouse Y position will be stored.
*/
AE_API void AEInputGetCursorPosition(s32 *pX, s32 *pY);
/**
* @brief Gets the change in position since the last AEInputUpdate() call.
*
* @param[in,out] pDeltaX Where the mouse change in X will be stored.
* @param[in,out] pDeltaY Where the mouse change in Y will be stored.
*/
AE_API void AEInputGetCursorPositionDelta(s32 *pDeltaX, s32 *pDeltaY);

/**
* @brief Sets whether the cursor will be displayed or not.
* @param[in] Show This is evaluated as a bool, 0 will not show the cursor, 
* all non-zero values will show the cursor.
*/
AE_API void AEInputShowCursor(int Show);
#endif
// ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // AE_INPUT_H

