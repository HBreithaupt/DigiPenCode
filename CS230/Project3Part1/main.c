// --------------------------------------------------------------------------------
// Project Name		:	Project 3 Part 1
// File Name		:	main.cpp
// Author			:	Haven Breithaupt
// Creation Date	:	02 - 23 - 2015
// Purpose			:	Implementation of the binary map functions
// History			:
//	- 2/23/15 created and completed
//� Copyright 1996-2015, DigiPen Institute of Technology (USA). All rights reserved.
// ---------------------------------------------------------------------------------



#include "BinaryMap.h"



int main(void)
{
	int Flag;
	float f;
	// Test here if you can read "Export.txt"
	ImportMapDataFromFile("Exported.txt");

	//Printing the information read by ImportMapDataFromFile
	// You should get (With the prodvided export file):
	
	// Width: 5
	// Height: 5
	// Map Data:
	// 1 1 1 1 1
	// 1 0 0 0 1
	// 1 4 2 0 1
	// 1 1 1 3 1
	// 1 1 1 1 1
	PrintRetrievedInformation();

	// Testing "GetCellValue"
	printf("\n\nTesting GetCellValue\n");
	printf("Cell (0,0) = %i\n", GetCellValue(0, 0));	//You should get 1
	printf("Cell (1,1) = %i\n", GetCellValue(1, 1));	//You should get 1	
	printf("Cell (1,2) = %i\n", GetCellValue(1, 2));	//You should get 0	
	printf("Cell (1,2) = %i\n", GetCellValue(1, 2));	//You should get 0	
	printf("Cell (3,4) = %i\n", GetCellValue(3, 4));	//You should get 1	
	printf("Cell (-1,1) = %i\n", GetCellValue(-1, 1));	//You should get 0	
	printf("Cell (1,-1) = %i\n", GetCellValue(1, -1));	//You should get 0	
	printf("Cell (5,1) = %i\n", GetCellValue(5, 1));	//You should get 0	
	printf("Cell (1,5) = %i\n", GetCellValue(1, 5));	//You should get 0

	// Testing "SnapToCell"
	printf("\n\nTesting SnapToCell\n");
	f = 0.2f;
	SnapToCell(&f);
	printf("0.2 got snapped to: %f\n", f);				//You should get 0.5

	f = 2.3f;
	SnapToCell(&f);
	printf("2.3 got snapped to: %f\n", f);				//You should get 2.5

	f = 1.7f;
	SnapToCell(&f);
	printf("1.7 got snapped to: %f\n", f);				//You should get 1.5

	f = 5.4f;
	SnapToCell(&f);
	printf("5.4 got snapped to: %f\n", f);				//You should get 5.5

	f = 4.9f;
	SnapToCell(&f);
	printf("4.9 got snapped to: %f\n", f);				//You should get 4.5

	//Testing "CheckInstanceBinaryMapCollision"
	printf("\n\nTesting CheckInstanceBinaryMapCollision\n");
	Flag = 0;
	Flag = CheckInstanceBinaryMapCollision(1.7f, 2.2f, 1.0f, 1.0f);
	printf("Flag for 1.7f, 2.2f, 1.0f, 1.0f is: %i\n", Flag);		//You should get 11
	
	Flag = 0;
	Flag = CheckInstanceBinaryMapCollision(3.4f, 1.7f, 1.0f, 1.0f);
	printf("Flag for 3.4f, 1.7f, 1.0f, 1.0f is: %i\n", Flag);		//You should get 1
	
	Flag = 0;
	Flag = CheckInstanceBinaryMapCollision(1.2f, 3.8f, 1.0f, 1.0f);
	printf("Flag for 1.2f, 3.8f, 1.0f, 1.0f is: %i\n", Flag);		//You should get 15

	FreeMapData();

	return 1;
}