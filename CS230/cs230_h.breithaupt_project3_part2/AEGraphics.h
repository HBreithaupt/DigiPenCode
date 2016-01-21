// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEGraphics.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/30
// Purpose			:	Graphics component header file
// History			:
// - 2008/01/30		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_GRAPHICS_H
#define AE_GRAPHICS_H

// ---------------------------------------------------------------------------
// Defines

typedef	enum
{
	AE_GFX_RM_NONE, 
	AE_GFX_RM_COLOR, 
	AE_GFX_RM_TEXTURE,
	

	AE_GFX_RM_NUM
}AEGfxRenderMode;


// ---------------------------------------------------------------------------


typedef enum
{
	AE_GFX_BM_NONE = 0, 
	AE_GFX_BM_BLEND,  
	AE_GFX_BM_ADD,  
	AE_GFX_BM_MULTIPLY,  

	AE_GFX_BM_NUM
}AEGfxBlendMode;


// ---------------------------------------------------------------------------


typedef enum
{
	AE_GFX_TM_PRECISE = 0,
	AE_GFX_TM_AVERAGE
}AEGfxTextureMode;


// ---------------------------------------------------------------------------

typedef enum
{
	AE_GFX_MDM_POINTS = 0,
	AE_GFX_MDM_LINES,
	AE_GFX_MDM_LINES_STRIP,
	AE_GFX_MDM_TRIANGLES,
	
	// Keep this one last
	AE_GFX_MDM_NUM
}AEGfxMeshDrawMode;

// ---------------------------------------------------------------------------

typedef enum
{
	AE_WOM_NORMAL = 0,
	AE_WOM_TOP_LEFT,

	
	// Keep this one last
	AE_WOM_NUM,
}WorldOriginMode;

// ---------------------------------------------------------------------------
// Struct/Class definitions

typedef struct AEGfxVertexBuffer AEGfxVertexBuffer;

typedef struct AEGfxVertexList
{
	AEGfxVertexBuffer		*mpVtxBuffer;
	u32                  vtxNum;
}AEGfxVertexList;

// ---------------------------------------------------------------------------

typedef struct AEGfxSurface AEGfxSurface;

typedef struct AEGfxTexture
{
	AEGfxSurface *mpSurface;
	char mpName[256];
}AEGfxTexture;

// ---------------------------------------------------------------------------
// Extern variables

// ---------------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------------

#ifdef __cplusplus

extern "C"
{
#endif

// ---------------------------------------------------------------------------


/************************************************************************************/
/************ These functions are used internally and should be ignored. ************/
/************************************************************************************/
/*****/AE_API int AEGfxInit(int Width, int Height);                            /*****/
/*****/DECLARE_FUNCTION_FOR_ANDROID_2_INT(AEGfxInit, int Width, int Height);   /*****/
/*****/AE_API void AEGfxReset();                                               /*****/
/*****///AE_API void AEGfxUpdate();                                            /*****/
/*****/AE_API void AEGfxExit();                                                /*****/
/*****/AE_API void AEGfxStart();                                               /*****/
/*****/DECLARE_FUNCTION_FOR_ANDROID(AEGfxStart);                               /*****/
/*****/AE_API void AEGfxEnd();                                                 /*****/
/*****/DECLARE_FUNCTION_FOR_ANDROID(AEGfxEnd);                                 /*****/
/************************************************************************************/
/************************************************************************************/


/**
 * @brief Sets the background color.
 * 
 * @param[in] Red The red component of the background color, from 0.0f - 1.0f
 * @param[in] Green The green component of the background color, from 0.0f - 1.0f
 * @param[in] Blue The blue component of the background color, from 0.0f - 1.0f
 */
AE_API void AEGfxSetBackgroundColor(float Red, float Green, float Blue);
/**
 * @brief Sets the render mode Alpha Engine will use for objects.
 * @details Tells Alpha Engine how objects should be rendered. 
 * typically you will use AE_GFX_RM_COLOR if you wish to specify the color,
 * or use AE_GFX_RM_TEXTURE if you wish to display an image over the object.
 * 
 * @param[in] RenderMode The AEGfxRenderMode enum to use.
 */
AE_API void AEGfxSetRenderMode(unsigned int RenderMode);

/**
 * @brief Gets the minimum X coordinate of the window.
 * @return The minimum X coordinate of the window.
 */
AE_API f32 AEGfxGetWinMinX(void);
/**
 * @brief Gets the maximum X coordinate of the window.
 * @return The maximum X coordinate of the window.
 */
AE_API f32 AEGfxGetWinMaxX(void);
/**
 * @brief Gets the minimum Y coordinate of the window.
 * @return The minimum Y coordinate of the window.
 */
AE_API f32 AEGfxGetWinMinY(void);
/**
 * @brief Gets the maximum Y coordinate of the window.
 * @return The maximum Y coordinate of the window.
 */
AE_API f32 AEGfxGetWinMaxY(void);

/**
 * @brief Sets the camera position.
 * @details Sets the position of the camera in world space.
 * 
 * @param X[in] The X coordinate to set for the camera.
 * @param Y[in] The Y coordinate to set for the camera.
 */
AE_API void AEGfxSetCamPosition(f32 X, f32 Y);
/**
 * @brief Gets the position of the camera.
 * @details Gets the position of the camera in world space.
 * 
 * @param[out] pX Pointer to the variable the X coordinate will be stored in.
 * @param[out] pY Pointer to the variable the Y coordinate will be stored in.
 */
AE_API void AEGfxGetCamPosition(f32 *pX, f32 *pY);

// Sets/Gets the camera distance, used to zoom in/out
//AE_API void AEGfxSetCamZoom(f32 Distance);
//AE_API f32 AEGfxGetCamZoom();


/**
 * @brief Sets a transformation matrix with only a translation
 * @details Sets the transformation matrix with translation but not rotation or scaling.
 * This is an easy way to move objects around before learning about more complex transformations.
 * 
 * @param X Translation along the X axis.
 * @param Y Translation along the Y axis.
 */
AE_API void AEGfxSetPosition(f32 X, f32 Y);

// functions to set the current transformation matrix to use
/**
 * @brief Sets the transformation matrix to map points to world space.
 * 
 * @param[in] pTransform The 3x3 matrix to transform
 */
AE_API void AEGfxSetTransform(float pTransform[3][3]);


/**
 * @brief Students should not use this function.
 * @details Sets the 3D transformation matrix. Not for use in CS230, CS529, or GAM150.
 * 
 * @param pTransform the 4x4 affine transformation matrix
 */
AE_API void AEGfxSetTransform3D(float pTransform[4][4]);
/**
 * @brief Builds and sets the transformation affine that maps objects to world space.
 * @details Takes the raw values for scale, rotation, and translation and builds a 2D affine.
 * It then uses that affine internally to map points to world space.
 * 
 * @param[in] PosX Translation along the X-axis
 * @param[in] PosY Translation along the Y-axis
 * @param[in] RotAngleDeg Rotation angle in degrees
 * @param[in] ScaleX Scale along the X-axis
 * @param[in] ScaleY Scale along the Y-axis
 */
AE_API void AEGfxSetFullTransform(float PosX, float PosY, float RotAngleDeg, float ScaleX, float ScaleY);
/**
 * @brief Builds and sets the transformation affine that maps objects to world space.
 * @details Takes the raw values for scale, rotation, and translation and builds a 2D affine.
 * It then uses that affine internally to map points to world space. This version also sets the layer of the object.
 * 
 * @param[in] PosX Translation along the X-axis
 * @param[in] PosY Translation along the Y-axis
 * @param[in] zOrder The layer to place the object on. Objects on lower layers will be under objects with higher layers.
 * @param[in] RotAngleDeg Rotation angle in degrees
 * @param[in] ScaleX Scale along the X-axis
 * @param[in] ScaleY Scale along the Y-axis
 */
AE_API void AEGfxSetFullTransformWithZOrder(float PosX, float PosY, float zOrder, float RotAngleDeg, float ScaleX, float ScaleY);

/**
 * @brief Sets a color that will be blended with the original material.
 * @details Sets a blend color to be applied on top of other objects.
 *  
 * @param[in] Red The red component of the blend color, from 0.0f - 1.0f
 * @param[in] Green The green component of the blend color, from 0.0f - 1.0f
 * @param[in] Blue The blue component of the blend color, from 0.0f - 1.0f
 * @param[in] Alpha The opacity (strength) of the blend, from 0.0f-1.0f
 */
AE_API void AEGfxSetBlendColor(float Red, float Green, float Blue, float Alpha);

/**
 * @brief Sets the transparency of the materials being drawn by Alpha Engine.
 * @details Sets the transparency for draws following the call. It will stay set to this value until changed.
 * 
 * @param[in] Alpha The opacity to set objects to.
 */
AE_API void AEGfxSetTransparency(float Alpha);

/**
 * @brief Sets a color that will be blended with the original material.
 * @details Sets a blend color to be applied on top of other objects.
 *  
 * @param[in] Red The red component of the blend color, from 0.0f - 1.0f
 * @param[in] Green The green component of the blend color, from 0.0f - 1.0f
 * @param[in] Blue The blue component of the blend color, from 0.0f - 1.0f
 * @param[in] Alpha The opacity (strength) of the blend, from 0.0f-1.0f
 */
AE_API void AEGfxSetTintColor(float Red, float Green, float Blue, float Alpha);

/**
 * @brief Sets the blend mode Alpha Engine should use.
 * @details Sets the blend mode. Options are:
 * AE_GFX_BM_NONE Doesn't blend 
 * AE_GFX_BM_BLEND Does blend
 * AE_GFX_BM_ADD Blends using addition (adds each color of overlapping pixels)
 * AE_GFX_BM_MULTIPLY Blends using multiplication (multiplies color values of overlapping pixels)
 * 
 * @param BlendMode The blend mode to use. Should be an AEGfxBlendMode enum value.
 */
AE_API void	AEGfxSetBlendMode(unsigned int BlendMode);

// Sets where the origin of the world is
/**
 * @brief Sets the mode for determining the origin of the world.
 * @details Sets where the origin is. Options are:
 * AE_WOM_NORMAL Origin is in the center
 * AE_WOM_TOP_LEFT Origin is the top left of the window
 * 
 * @param[in] WorldOriginMode The WorldOriginMode enum value corresponding to the mode you want.
 */
AE_API void	AEGfxSetWorldOriginMode(unsigned int WorldOriginMode);

/**
 * @brief Sets the viewport position and size.
 * @details Sets the viewport position and size. Only needed if the main window has multiple viewports.
 * Set a parameter to a negative value to reset to the full window space.
 * 
 * @param ViewportX Viewport X-coord in world space
 * @param ViewportY Viewport Y-coord in world space
 * @param ViewportWidth Width of the viewport
 * @param ViewportHeight Height of the viewport
 */
AE_API void AEGfxSetViewportPositionAndDimensions(int ViewportX, int ViewportY, int ViewportWidth, int ViewportHeight);


// functions to create a mesh

//AE_API void			AEGfxTriListInitialize	(AEGfxTriList *pTriList);

/**
 * @brief Tells Alpha Engine to begin building a mesh.
 * @details Use this function before AEGfxTriAdd and AEGfxVertexAdd to tell AE
 * that you are building a new mesh.
 */
AE_API void			AEGfxMeshStart	();
/**
 * @brief Adds a triangle to the current Mesh.
 * @details [long description]
 * 
 * @param x0 x coordinate of the first vertex
 * @param y0 Y coordinate of the first vertex
 * @param c0 RGBA values for the first vertex (ie 0xFF00FFFF)
 * @param tu0 [description]
 * @param tv0 [description]
 * @param x1 X coordinate of the second vertex
 * @param y1 Y coordinate of the second vertex
 * @param c1 RGBA values for the second vertex
 * @param tu1 [description]
 * @param tv1 [description]
 * @param x2 X coordinate of the third vertex
 * @param y2 Y coordinate of the third vertex
 * @param c2 RGBA values for the third vertex
 * @param tu2 [description]
 * @param tv2 [description]
 */
AE_API void			AEGfxTriAdd		(f32 x0, f32 y0, u32 c0, f32 tu0, f32 tv0,
										 f32 x1, f32 y1, u32 c1, f32 tu1, f32 tv1,
										 f32 x2, f32 y2, u32 c2, f32 tu2, f32 tv2);

/**
 * @brief Adds a vertex to the current Mesh.
 * @details [long description]
 * 
 * @param x0 X coordinate of the vertex
 * @param y0 Y coordinate of the vertex
 * @param c0 RGBA values of the vertex (ie 0x00FF00FF)
 * @param tu0 [description]
 * @param tv0 [description]
 */
AE_API void			AEGfxVertexAdd		(f32 x0, f32 y0, u32 c0, f32 tu0, f32 tv0);

/**
 * @brief Tells Alpha Engine that you are done building the mesh.
 * @details Used after AEGfxMeshStart() and adding triangles and/or vertices to signal the end of the mesh.
 * @return Returns a pointer to the AEGfxVertList instance that was created.
 */
AE_API AEGfxVertexList*	AEGfxMeshEnd		();
/**
 * @brief Draws a mesh with a user-specified mode.
 * 
 * @param pVertexList pointer to the vertex list containing the mesh to be drawn.
 * @param int The draw mode to use for the Mesh. Use an AEGfxMeshDrawMode enum:
 * AE_GFX_MDM_POINTS
 * AE_GFX_MDM_LINES
 * AE_GFX_MDM_LINES_STRIP
 * AE_GFX_MDM_TRIANGLES
 */
AE_API void				AEGfxMeshDraw	(AEGfxVertexList* pVertexList, unsigned int MeshDrawMode);
/**
 * @brief Draws a mesh without a user defined draw mode.
 * 
 * @param pVertexList Pointer to the mesh.
 */
AE_API void				AEGfxMeshFree	(AEGfxVertexList* pVertexList);

/**
* @brief Loads a texture from file into memory.
*
* @param[in] pFileName The name and path of the file to be loaded from disk.
* @return Returns a pointer to the AEGfxTexture instance containing the texture that was loaded.
*/
AE_API AEGfxTexture*	AEGfxTextureLoad(const char *pFileName);

/**
* @brief Unloads a texture that was loaded into memory. This must be used to prevent memory leaks
* @param[in] pTexture Pointer the the AEGfxTexture instance to be freed.
*/
AE_API void				AEGfxTextureUnload(AEGfxTexture *pTexture);

/**
* @brief Sets the texture to be drawn on the current object
* @details This should be used while drawing an object. It sets the texture and offset.
* The offset can be used for things like jumping between different sprites on a sprite sheet.
* Use NULL for no texture.
* 
* @param[in] pTexture The texture to draw on the object.
* @param[in] offset_x The amount to offset the texture along the x-axis.
* @param[in] offset_y The amount to offset the texture along the y-axis.
*/
AE_API void				AEGfxTextureSet(AEGfxTexture *pTexture, f32 offset_x, f32 offset_y);


AE_API AEGfxTexture*	AEGfxTextureLoadFromMemory(unsigned char *pColors, unsigned int Width, unsigned int Height);

/**
* @brief Saves a texture to a file on disk.
*
* @param[in] pTexture The texture to save to file.
* @param[in] pFileName The name to save the file with.
*/
AE_API void				AEGfxSaveTextureToFile(AEGfxTexture* pTexture, char *pFileName);

/**
* @brief Sets the texture mode to be used for the current object being drawn.
*
* param[in] TextureMode Takes one of the following AEGfxTextureMode enums:
* AE_GFX_TM_PRECISE
* AE_GFX_TM_AVERAGE
*/
AE_API void				AEGfxSetTextureMode(unsigned int TextureMode);

/**
 * @brief Gets the position of a pixel in worldspace.
 * 
 * @param[in] ScreenX The screen X-coord
 * @param[in] ScreenY The screen Y-coord
 * @param[out] pWorldX The corresponding world X-coord
 * @param[out] pWorldY The corresponding world Y-coord
 */
AE_API void				AEGfxConvertScreenCoordinatesToWorld(float ScreenX, float ScreenY, float *pWorldX, float *pWorldY);

// functions to draw simple primitives
// * these are slow!!! use with caution!!
// * DO NOT call any of these functions while building mesh using the above functions
AE_API void			AEGfxPoint		(f32 x0, f32 y0, f32 z0, u32 c0);
AE_API void			AEGfxLine		(f32 x0, f32 y0, f32 z0, f32 r0, f32 g0, f32 b0, f32 a0, f32 x1, f32 y1, f32 z1, f32 r1, f32 g1, f32 b1, f32 a1);

AE_API void			AEGfxTri		(f32 x0, f32 y0, f32 z0, u32 c0, 
								 f32 x1, f32 y1, f32 z1, u32 c1, 
								 f32 x2, f32 y2, f32 z2, u32 c2);
AE_API void			AEGfxQuad		(f32 x0, f32 y0, f32 z0, u32 c0, 
								 f32 x1, f32 y1, f32 z1, u32 c1, 
								 f32 x2, f32 y2, f32 z2, u32 c2, 
								 f32 x3, f32 y3, f32 z3, u32 c3);
AE_API void			AEGfxBox		(f32 x0, f32 y0, f32 z0, f32 sizeX, f32 sizeY, f32 sizeZ, u32 c0, u32 c1);
AE_API void			AEGfxSphere		(f32 x0, f32 y0, f32 z0, f32 radius, u32 c0, u32 c1, u32 division);
AE_API void			AEGfxCone		(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 radius, u32 c0, u32 c1, u32 division);
AE_API void			AEGfxAxis		(f32 scale);

AE_API u32			AEGfxColInterp	(u32 c0, u32 c1, f32 t);


// font related functions
// This function has been deprecated.
//AE_API void			AEGfxPrint		(s32 x, s32 y, u32 color, s8* pStr);

/************************************************************************************/
/************ These functions should be ignored and not used by students ************/
/************************************************************************************/
#if(EXPORT_WINDOWS == 1)
AE_API HDC			AEGfxGetDeviceContext(void);
AE_API HGLRC		AEGfxGetRenderContext(void);
AE_API int			AEGfxGetPixelFormat(void);
#endif

// ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // AE_GRAPHICS_H

