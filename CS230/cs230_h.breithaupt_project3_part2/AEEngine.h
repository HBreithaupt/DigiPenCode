// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEEngine.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	the main include file for the Alpha engine
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_ENGINE_H
#define AE_ENGINE_H

// ---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include  "AEExport.h"

#if(1 == EXPORT_WINDOWS)

#include <windows.h>
#include <windowsx.h>

#endif
// ---------------------------------------------------------------------------




// ---------------------------------------------------------------------------
/// assert defines

#ifndef FINAL

// ---------------------------------------------------------------------------

#define AE_ASSERT(x)												\
{																	\
	if((x) == 0)													\
	{																\
		PRINT("AE_ASSERT: %s\nLine: %d\nFunc: %s\nFile: %s\n",		\
			#x, __LINE__, __FUNCTION__, __FILE__); 					\
		exit(1);													\
	}																\
}

// ---------------------------------------------------------------------------

#define AE_ASSERT_MESG(x, ...)										\
{																	\
	if((x) == 0)													\
	{																\
		PRINT("AE_ASSERT_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__);					\
		PRINT("Mesg: "__VA_ARGS__);									\
		PRINT("\n");												\
		exit(1);													\
	}																\
}

// ---------------------------------------------------------------------------

#define AE_ASSERT_PARM(x)											\
{																	\
	if((x) == 0)													\
	{																\
		PRINT("AE_ASSERT_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__);					\
		exit(1);													\
	}																\
}

// ---------------------------------------------------------------------------

#define AE_ASSERT_ALLOC(x)												\
{																		\
	if((x) == 0)														\
	{																	\
		PRINT("AE_ASSERT_ALLOC: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__);						\
		exit(1);														\
	}																	\
}


// ---------------------------------------------------------------------------

#define AE_WARNING(x)											\
{																\
	if((x) == 0)												\
	{															\
		PRINT("AE_WARNING: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__); 				\
	}															\
}

// ---------------------------------------------------------------------------

#define AE_WARNING_MESG(x, ...)											\
{																		\
	if((x) == 0)														\
	{																	\
		PRINT("AE_WARNING_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__);						\
		PRINT("Mesg: "__VA_ARGS__);										\
		PRINT("\n");													\
	}																	\
}

// ---------------------------------------------------------------------------

#define AE_WARNING_PARM(x)												\
{																		\
	if((x) == 0)														\
	{																	\
		PRINT("AE_WARNING_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__);						\
	}																	\
}

// ---------------------------------------------------------------------------

#else // FINAL

// ---------------------------------------------------------------------------

#define AE_ASSERT(x)
#define AE_ASSERT_MESG(x, ...)
#define AE_ASSERT_PARM(x)
#define AE_ASSERT_ALLOC(x)

#define AE_WARNING(x)
#define AE_WARNING_MESG(x, ...)
#define AE_WARNING_PARM(x)
#define AE_WARNING_ALLOC(x)

// ---------------------------------------------------------------------------

#endif // FINAL

// ---------------------------------------------------------------------------

#define AE_FATAL_ERROR(...)					\
{											\
	PRINT("AE_FATAL_ERROR: "__VA_ARGS__);	\
	exit(1);								\
}


// ---------------------------------------------------------------------------
// Alpha engine includes

#include "AETypes.h"
#include "AEMath.h"
#include "AEUtil.h"
#include "AEFrameRateController.h"
#include "AESystem.h"
#include "AEGraphics.h"
#include "AEInput.h"
#include "AEGameStateMgr.h"

// ---------------------------------------------------------------------------

#endif // ENGINE_H

