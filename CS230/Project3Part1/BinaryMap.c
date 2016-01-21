// --------------------------------------------------------------------------------
// Project Name		:	Project 3 Part 1
// File Name		:	BinaryMap.cpp
// Author			:	Haven Breithaupt
// Creation Date	:	02 - 23 - 2015
// Purpose			:	Implementation of the binary map functions
// History			:
//	- 2/23/15 created and completed
//� Copyright 1996-2015, DigiPen Institute of Technology (USA). All rights reserved.
// ---------------------------------------------------------------------------------


#include "BinaryMap.h"


#pragma warning(disable: 4996)

/*The number of horizontal elements*/
static int BINARY_MAP_WIDTH;

/*The number of vertical elements*/
static int BINARY_MAP_HEIGHT;

/*This will contain all the data of the map, which will be retireved from a file
when the "ImportMapDataFromFile" function is called*/
static int **MapData;

/*This will contain the collision dataof the binary map. It will be filled in the 
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element 
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
static int **BinaryCollisionArray;



int GetCellValue(unsigned int X, unsigned int Y)
{
    if(X < 0 || Y < 0)
      return 0;
  
    if(X >= (unsigned)BINARY_MAP_WIDTH || Y >= (unsigned)BINARY_MAP_HEIGHT)
      return 0;
	
    return BinaryCollisionArray[X][Y];
}

int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
  int Flag = 0;
  
  float xr1, yr1, xr2, yr2, xl1, yl1, xl2, yl2, xt1, yt1, xt2, yt2, xb1, yb1, xb2, yb2;
  
  /* right hotspots */
    
    /* right top*/
  xr1 = PosX + scaleX/2;
  yr1 = PosY + scaleY/4;
    
    /* right bottom */
  xr2 = PosX + scaleX/2;
  yr2 = PosY - scaleY/4;
  
  /* left hotspots */
    
    /* left top */
  xl1 = PosX - scaleX/2;
  yl1 = PosY + scaleY/4;
    
    /* left bottom */
  xl2 = PosX - scaleX/2;
  yl2 = PosY - scaleX/4;
    
  /* top hotspots */
    
    /* top right */
  xt1 = PosX + scaleX/4;
  yt1 = PosY + scaleY/2;
  
    /* top left */
  xt2 = PosX - scaleX/4;
  yt2 = PosY + scaleY/2;
    
  /* bottom hotspots */
  
    /* bottom right */
  xb1 = PosX - scaleX/4;
  yb1 = PosX + scaleY/2;
  
    /* bottom left */
  xb2 = PosX - scaleX/4;
  yb2 = PosX - scaleY/2;
 
if(GetCellValue((int)xr1,(int)yr1))
  Flag |= COLLISION_RIGHT;
  
  /* right bottom */
if(GetCellValue((int)xr2,(int)yr2))
  Flag |= COLLISION_RIGHT;
  
  /* left top */
if(GetCellValue((int)xl1,(int)yl1))
  Flag |= COLLISION_LEFT;
  
  /* left bottom */
if(GetCellValue((int)xl2,(int)yl2))
  Flag |= COLLISION_LEFT;
  
  /* top right */
if(GetCellValue((int)xt1,(int)yt1))
  Flag |= COLLISION_TOP;
  
  /* top left */
if(GetCellValue((int)xt2,(int)yt2))
  Flag |= COLLISION_TOP;
  
  /* bottom right */
if(GetCellValue((int)xb1,(int)yb1))
  Flag |= COLLISION_BOTTOM;
  
  /* bottom left */
if(GetCellValue((int)xb2,(int)yb2))
  Flag |= COLLISION_BOTTOM;
  
  return Flag;
  
}

void SnapToCell(float *Coordinate)
{
 
  	*Coordinate = (int)*Coordinate + 0.5f;
	
}

int ImportMapDataFromFile(char *FileName)
{
	FILE *fp;
	
	fp = fopen(FileName, "r");
	int input;
  
    if(fp)
    {
      fscanf(fp, "Width %i\n", &BINARY_MAP_WIDTH);
      fscanf(fp, "Height %i", &BINARY_MAP_HEIGHT);
      
      MapData = (int **) malloc(BINARY_MAP_HEIGHT * sizeof(int));
      BinaryCollisionArray = (int **) malloc(BINARY_MAP_HEIGHT * sizeof(int));

	  for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	  {
		  MapData[i] = (int *)malloc(BINARY_MAP_WIDTH * sizeof(int));
		  BinaryCollisionArray[i] = (int *)malloc(BINARY_MAP_WIDTH * sizeof(int));
	  }
      
      for(int row = BINARY_MAP_HEIGHT - 1; row >= 0; row--)
      {
        for(int column = 0;  column < BINARY_MAP_WIDTH; column++)
        {
			fscanf(fp, "%i", &input);

			MapData[column][row] = input;

			if (input > 1)
				BinaryCollisionArray[column][row] = 0;
			else
				BinaryCollisionArray[column][row] = input;
        }
      }
      
     
	  fclose(fp);
      return 1;
      
    }
    else
    {
      return 0;
    }

	
}

void FreeMapData(void)
{
	for (int i = 0; i < BINARY_MAP_HEIGHT; i++)
	{
		free(MapData[i]);
		free(BinaryCollisionArray[i]);
	}

	free(MapData);
	free(BinaryCollisionArray);
}

void PrintRetrievedInformation(void)
{
	int i, j;

	printf("Width: %i\n", BINARY_MAP_WIDTH);
	printf("Height: %i\n", BINARY_MAP_HEIGHT);

	printf("Map Data:\n");
	for(j = BINARY_MAP_HEIGHT - 1; j >= 0; --j)
	{
		for(i = 0; i < BINARY_MAP_WIDTH; ++i)
		{
			printf("%i ", MapData[i][j]);
		}

		printf("\n");
	}

	printf("\n\nBinary Collision Data:\n");
	for(j = BINARY_MAP_HEIGHT - 1; j >= 0; --j)
	{
		for(i = 0; i < BINARY_MAP_WIDTH; ++i)
		{
			printf("%i ", BinaryCollisionArray[i][j]);
		}

		printf("\n");
	}
}