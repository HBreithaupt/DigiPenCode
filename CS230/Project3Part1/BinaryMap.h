// --------------------------------------------------------------------------------
// Project Name		:	Project 3 Part 1
// File Name		:	BinaryMap.h
// Author			:	Haven Breithaupt
// Creation Date	:	02 - 23 - 2015
// Purpose			:	Prototypes of BinaryMap.cpp
// History			:
//	- 2/23/15 created and completed
//� Copyright 1996-2015, DigiPen Institute of Technology (USA). All rights reserved.
// ---------------------------------------------------------------------------------


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define	COLLISION_LEFT		0x00000001	//0001
#define	COLLISION_RIGHT		0x00000002	//0010
#define	COLLISION_TOP		0x00000004	//0100
#define	COLLISION_BOTTOM	0x00000008	//1000


enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN			//4
};


/*This function retrieves the value of the element (X;Y) in BinaryCollisionArray.
Before retrieving the value, it should check that the supplied X and Y values
are not out of bounds (in that case return 0)*/
int GetCellValue(unsigned int X, unsigned int Y);


/*This function creates 2 hot spots on each side of the object instance, and checks 
if each of these hot spots is in a collision area (which means the cell if falls in has
a value of 1).
At the beginning of the function, a "Flag" integer should be initialized to 0.
Each time a hot spot is in a collision area, its corresponding bit in "Flag" is set to 1.
Finally, the function returns the integer "Flag"
The position of the object instance is received as PosX and PosY
The size of the object instance is received as scaleX and scaleY

Note: For this project, you can assume that the object instance's size is 1 by 1 (the size of 1 tile)

Creating the hotspots:
	-Handle each side separately.
	-2 hot spots are needed for each collision side.
	-These 2 hot spots should be positioned on 1/4 above the center and 1/4 below the center

Example: Finding the hotspots on the left side of the object instance

	float x1, y1, x2, y2;

	-hotspot 1
	x1 = PosX - scaleX/2	To reach the left side
	y1 = PosY + scaleY/4	To go up 1/4 of the height
	
	-hotspot 2
	x2 = PosX - scaleX/2	To reach the left side
	y2 = PosY - scaleY/4	To go down 1/4 of the height
*/
int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY);


/*This function snaps the value sent as parameter to the center of the cell.
It is used when a sprite is colliding with a collision area from one or more side.
To snap the value sent by "Coordinate", find its integral part by type casting it
to an integer, then add 0.5 (which is half the cell's width or height)
*/
void SnapToCell(float *Coordinate);


/*This function opens the file name "FileName" and retrieves all the map data.
	It allocates memory for the 2 arrays: MapData & BinaryCollisionArray
	The first line in this file is the width of the map.
	The second line in this file is the height of the map.
	The remaining part of the file is a series of numbers
	Each number represents the ID (or value) of a different element in the doubel dimensionaly array.

	Example:

	Width 5
	Height 5
	1 1 1 1 1
	1 0 0 0 1
	1 4 2 0 1
	1 1 1 3 1
	1 1 1 1 1


	After importing the above data, "MapData" and " BinaryCollisionArray" should be

	1 1 1 1 1
	1 0 0 0 1
	1 4 2 0 1
	1 1 1 3 1
	1 1 1 1 1

	and

	1 1 1 1 1
	1 0 0 0 1
	1 0 0 0 1
	1 1 1 0 1
	1 1 1 1 1

	respectively.
	
Finally, the function returns 1 if the file named "FileName" exists, otherwise it returns 0*/
int ImportMapDataFromFile(char *FileName);

/*This function frees the memory that was allocated for the 2 arrays MapData 
& BinaryCollisionArray which was allocated in the "ImportMapDataFromFile" function*/
void FreeMapData(void);


void PrintRetrievedInformation();