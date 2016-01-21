// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AESystem.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	header file for the system module
// History			:
// - 2008/01/31		:	- initial implementation
// - 2014/10/15 	: - Initial documentation
// ---------------------------------------------------------------------------

#ifndef AE_SYSTEM_H
#define AE_SYSTEM_H

#include "AEExport.h"
#include "AETypes.h"

// ---------------------------------------------------------------------------

// window related variables
#if(EXPORT_WINDOWS == 1)
extern HWND			gAESysWindowHandle;
#endif

// ---------------------------------------------------------------------------


/**
* @brief This struct is used by Alpha Engine to initialize the internal systems.
* @details Create an instance of this struct and fill out the details to
* initialize Alpha Engine.
*/
typedef struct AESysInitInfo
{
#if(EXPORT_WINDOWS == 1)
  /**
	* @par
	* Whether Alpha Engine should create the window.
	* This is evaluated as a bool, 0 will not create the window, any other value will.
	*/
	int				mCreateWindow;
	HWND			mWindowHandle;
	/**
	* @par
	* This is supplied as a parameter to WinMain().
	* Use the first parameter from WinMain().
	*/
	HINSTANCE		mAppInstance;
	/**
	* @par
	* This is supplied as a parameter to WinMain().
	* Use the fourth parameter from WinMain().
	*/
	int				mShow;
	/**
	* @par
	* Specifies the width and height of the window created by Alpha Engine.
	* Note that mCreateWindow must be a non-zero value for the window to be created.
	*/
	int				mWinWidth, mWinHeight;
	/**
	* @par
	* Specify if an AE console should be created. This is NOT a debug console,
	* functions that use stdout will not output to this console.
	* To create a console that works with printf() and similar, use the following:
	*
	*    AllocConsole();
	*    freopen("CONOUT$", "w", stdout);
	*
	* This creates a console and sets that console's output to be what is written to stdout.
	* mCreateConsole does not need to be true for those two functions to work.
	*/
	int				mCreateConsole;
	/**
	* @par
	* Sets the Alpha Engine framerate controller's max framerate. Defaults to 60.
	*/
	unsigned int	mMaxFrameRate;
	/**
	* @par
	* specifies the message handling callback function.
	* If you are unsure, use NULL to use the default message handler.
	*/
	LRESULT (CALLBACK *mpWinCallBack)(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	/**
	* @par
	* This is a bitfield for the class style options. Use
	*     CS_HREDRAW | CS_VREDRAW
	*/
	unsigned int	mClassStyle;
	/**
	* @par
	* This is a bitfield for the Window Style options. Use WS_OVERLAPPEDWINDOW if unsure.
	*/
	unsigned int	mWindowStyle;
	/**
	* @par
	* Specifies whether Alpha Engine should handle the window for you.
	* This should be set to 1 or your window will not be responsive.
	*/
	unsigned int	mHandleWindowMessages;



#else
	int dummy;

#endif
}AESysInitInfo;


// ---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif

#if(EXPORT_WINDOWS == 1)
/**
* @brief Initializes the Alpha Engine Systems.
* @details Uses the specified options to initialize Alpha Engine and
* the functionality handled by Alpha Engine.
*
* @param[in] pSysInitInfo Pointer to the user-defined settings to initialize
* Alpha Engine with. The struct instance should have the following members:
*     HINSTANCE hAppInstance,
*     int show,
*     int WinHeight,
*		  int WinWidth,
*		  int CreateConsole,
*     unsigned int FrameRateMax,
*      LRESULT (CALLBACK *pWinCallBack)(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp))
*/
AE_API int AESysInit(AESysInitInfo *pSysInitInfo);
AE_API void AESysReset();
AE_API void AESysUpdate();
AE_API void AESysExit();


AE_API HWND AESysGetWindowHandle	();
//AE_API int* AESysGetAppActive		();
/**
* @brief Sets the title of the window being used by Alpha Engine.
* @param[in] pTitle The null-terminated c-style string that the window title
* will be set to.
*/
AE_API void AESysSetWindowTitle		(const char *pTitle);
/**
* @brief Checks if a window being managed by Alpha Engine exists.
*
* @return Boolean [0,1] int. 0 if there is no window, 1 if there is.
*/
AE_API int AESysDoesWindowExist		();


// ---------------------------------------------------------------------------
/**
* @brief Tells Alpha Engine that it is beginning a new frame.
*
* @detail This functions tells Alpha Engine to start drawing a new frame.
* This will flush the old data. It should be called at the beginning of every
* frame, typically as the first call in some sort of Draw() function in a game
* engine update loop.
*/
AE_API void AESysFrameStart();
/**
* @brief Tells Alpha Engine that everything has been added to the frame.
*
* @detail At the end of a frame this tells Alpha Engine that the frame is
* finished and that it can draw it to the screen.
*/
AE_API void AESysFrameEnd();

// ---------------------------------------------------------------------------


AE_API void AESysAddCustomCallBack(u32 MsgID, LRESULT (*pCallBack)(HWND hWin, UINT msg, WPARAM wp, LPARAM lp));
AE_API void AESysRemoveCustomCallBack(u32 MsgID, LRESULT (*pCallBack)(HWND hWin, UINT msg, WPARAM wp, LPARAM lp));
AE_API void AESysClearCustomCallBacks();
#endif

#ifdef __cplusplus
}
#endif

#endif // AE_SYSTEM_H

