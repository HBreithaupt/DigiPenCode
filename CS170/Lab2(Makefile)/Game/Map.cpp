#include <stdio.h>
#include "Map.h"
#include "Inventory.h"

/*Map Size*/
#define MapSize 3

/*Current Map*/
unsigned int Map[MapSize * MapSize] = 
{
	MapCell_Gold,		MapCell_Locked,			MapCell_Dark,
	MapCell_Void,		MapCell_Empty,			MapCell_Void,
	MapCell_Lighter,	MapCell_Candle,			MapCell_Dark | MapCell_Key
};

/*Current Position*/
unsigned int CurrentPosition = (MapSize/2) * (1 + MapSize);

/*Candle Status*/
unsigned char CandleLit = 0;

/*Function to Get Current Position*/
void GetCurrentPosition(int* CurrentPositionX, int* CurrentPositionY)
{
	/*Get Current Position*/
	(*CurrentPositionX) = CurrentPosition % MapSize;
	(*CurrentPositionY) = CurrentPosition / MapSize;
}

/*Function to Get Current Cell*/
unsigned int GetCurrentCell(void)
{
	/*Get Current Cell*/
	return Map[CurrentPosition];
}

/*Function to Look*/
void Look(int NewPositionX, int NewPositionY)
{
	/*Validate New Position*/
	if(NewPositionX < 0 || NewPositionX >= MapSize || NewPositionY < 0 || NewPositionY >= MapSize)
	{
		/*Display Message*/
		printf("It Looks Like The End Of The Map...\n");
	}
	else
	{
		/*Get New Position*/
		unsigned int NewPosition = NewPositionX + MapSize * NewPositionY;
		/*Get Current Cell*/
		unsigned int CurrentCell = Map[NewPosition];
		/*Check If Void Cell*/
		unsigned char Empty = 1;
		if(CurrentCell & MapCell_Void)
		{
			/*Display Message*/
			printf("It's A Void Cell...\n");
			return;
		}
		/*Check If Dark Cell*/
		if(CurrentCell & MapCell_Dark)
		{
			/*Check If Candle Is Lit*/
			if(!CandleLit)
			{
				/*Display Message*/
				printf("So Dark Can't See Anything...\n");
				return;
			}
		}
		/*Check If Locked Cell*/
		if(CurrentCell & MapCell_Locked)
		{
			/*Display Message*/
			printf("There's A Locked Door...\n");
			return;
		}
		/*Check Win Condition*/
		if(CurrentCell & MapCell_Gold)
		{
			/*Display Message*/
			printf("There Is The Gold!\n");
			return;
		}

		/*Update Inventory*/
		if(CurrentCell & MapCell_Key)
		{
			/*Display Message*/
			Empty = 0;
			printf("There Is A Key!\n");
		}
		if(CurrentCell & MapCell_Candle)
		{
			/*Display Message*/
			Empty = 0;
			printf("There Is A Candle!\n");

		}
		if(CurrentCell & MapCell_Lighter)
		{
			/*Display Message*/
			Empty = 0;
			printf("There Is A Lighter!\n");
		}
		/*If Cell Is Empty*/
		if(Empty)
		{
			/*Display Message*/
			printf("There's Nothing There\n");
		}
	}
}

/*Function to Update Player Stats*/
char UpdateStats(int NewPositionX, int NewPositionY)
{
	/*Validate New Position*/
	if(NewPositionX < 0 || NewPositionX >= MapSize || NewPositionY < 0 || NewPositionY >= MapSize)
	{
		/*Display Message*/
		printf("Can't Move That Way...\n");
		return -1;
	}
	else
	{
		/*Get New Position*/
		unsigned int NewPosition = NewPositionX + MapSize * NewPositionY;
		/*Get Current Cell*/
		unsigned int CurrentCell = Map[NewPosition];
		
		/*Check If Void Cell*/
		if(CurrentCell & MapCell_Void)
		{
			/*Display Message*/
			printf("Can't Move To Void Cell...\n");
			return -1;
		}
		/*Check If Dark Cell*/
		if(CurrentCell & MapCell_Dark)
		{
			/*Check If Candle Is Lit*/
			if(!CandleLit)
			{
				/*Display Message*/
				printf("It's Too Dark To See Here...\n");
				return -1;
			}
		}
		/*Check If Locked Cell*/
		if(CurrentCell & MapCell_Locked)
		{
			/*Display Message*/
			printf("Door Locked...\n");
			return -1;
		}

		/*Update Current Position*/
		CurrentPosition = NewPosition;

		/*Check Win Condition*/
		if(CurrentCell & MapCell_Gold)
		{
			/*Display Message*/
			printf("Gold Found!\n");
			return 1;
		}

		/*Update Inventory*/
		if(CurrentCell & MapCell_Key)
		{
			/*Display Message*/
			printf("Found Key!\n");
		}
		if(CurrentCell & MapCell_Candle)
		{
			/*Display Message*/
			printf("Found Candle!\n");

		}
		if(CurrentCell & MapCell_Lighter)
		{
			/*Display Message*/
			printf("Found Lighter!\n");
		}
	}
	/*Status Updated*/
	return 0;
}

/*Function to Take Item*/
char TakeItem(enum ItemType CurrentItem)
{
	/*Get Current Cell*/
	unsigned int CurrentCell = Map[CurrentPosition];
	/*Update Inventory*/
	if((CurrentItem == ItemType_Key) && (CurrentCell & MapCell_Key))
	{
		/*Add Key To Inventory*/
		AddItem(ItemType_Key);
		/*Remove Key From Map*/
		Map[CurrentPosition] &= ~MapCell_Key;
		/*Display Message*/
		printf("Key Taken!\n");
		return 1;
	}
	if((CurrentItem == ItemType_Candle) && (CurrentCell & MapCell_Candle))
	{
		/*Add Key To Inventory*/
		AddItem(ItemType_Candle);
		/*Remove Key From Map*/
		Map[CurrentPosition] &= ~MapCell_Candle;
		/*Display Message*/
		printf("Candle Taken!\n");
		return 1;

	}
	if((CurrentItem == ItemType_Lighter) && (CurrentCell & MapCell_Lighter))
	{
		/*Add Key To Inventory*/
		AddItem(ItemType_Lighter);
		/*Remove Key From Map*/
		Map[CurrentPosition] &= ~MapCell_Lighter;
		/*Display Message*/
		printf("Lighter Taken!\n");
		return 1;
	}
	/*Display Message*/
	printf("Item Not Found...\n");
	/*Item Not Found*/
	return 0;
}

char UseItem(enum ItemType CurrentItem)
{
	/*Update Inventory*/
	if(CurrentItem == ItemType_Key)
	{	
		/*Query Item*/
		if(!QueryItem(ItemType_Key))
		{
			/*Display Message*/
			printf("You Don't Have A Key...\n");
		}
		else
		{
			/*Display Message*/
			printf("Maybe You Should Try Opening The Door...\n");
		}
	}
	if(CurrentItem == ItemType_Candle)
	{
		/*Query Item*/
		if(!QueryItem(ItemType_Candle))
		{
			/*Display Message*/
			printf("You Don't Have A Candle...\n");
		}
		else
		{
			/*Display Message*/
			printf("An Unlit Candle Is Useless...\n");
		}
	}
	if(CurrentItem == ItemType_Lighter)
	{
		/*Query Item*/
		if(!QueryItem(ItemType_Lighter))
		{
			/*Display Message*/
			printf("You Don't Have A Lighter...\n");
		}
		else
		{
			/*Query Candle*/
			if(QueryItem(ItemType_Candle))
			{
				/*Light Candle*/
				CandleLit = 1;
				/*Display Message*/
				printf("Candle Lit!\n");
				return 1;
			}
			else
			{
				/*Display Message*/
				printf("But There's Nothing To Light...\n");
			}
		}
	}

	/*Item Not Found*/
	return 0;
}

char OpenDoor(void)
{
	/*Query Key*/
	if(!QueryItem(ItemType_Key))
	{
		/*Display Message*/
		printf("You Don't Have A Key...\n");
	}
	else
	{
		/*Get Current Position*/
		int CurrentPositionX, CurrentPositionY;
		GetCurrentPosition(&CurrentPositionX, &CurrentPositionY);
		/*Get Locked Cells*/
		if((CurrentPositionX + 1 < MapSize) && (Map[(CurrentPositionX + 1) + MapSize * CurrentPositionY] & MapCell_Locked))
		{
			/*Remove Locked From Map*/
			Map[(CurrentPositionX + 1) + MapSize * CurrentPositionY] &= ~MapCell_Locked;
			/*Display Message*/
			printf("Right Door Open!\n");
			return 1;
		}
		else if((CurrentPositionX - 1 >= 0) && (Map[(CurrentPositionX - 1) + MapSize * CurrentPositionY] & MapCell_Locked))
		{
			/*Remove Locked From Map*/
			Map[(CurrentPositionX - 1) + MapSize * CurrentPositionY] &= ~MapCell_Locked;
			/*Display Message*/
			printf("Left Door Open!\n");
			return 1;
		}
		else if((CurrentPositionY - 1 >= 0) && (Map[CurrentPositionX + MapSize * (CurrentPositionY - 1)] & MapCell_Locked))
		{
			/*Remove Locked From Map*/
			Map[CurrentPositionX + MapSize * (CurrentPositionY - 1)] &= ~MapCell_Locked;
			/*Display Message*/
			printf("Up Door Open!\n");
			return 1;
		}
		else if((CurrentPositionY + 1 < MapSize) && (Map[CurrentPositionX + MapSize * (CurrentPositionY + 1)] & MapCell_Locked))
		{
			/*Remove Locked From Map*/
			Map[CurrentPositionX + MapSize * (CurrentPositionY + 1)] &= ~MapCell_Locked;
			/*Display Message*/
			printf("Down Door Open!\n");
			return 1;
		}
		else
		{
			/*Display Message*/
			printf("But There's Nothing Locked Here...\n");
		}
	}
	/*Door Not Open*/
	return 0;
}

void SaveMap(FILE* Out)
{
	/*Save Current Position*/
	fwrite(&CurrentPosition, sizeof(unsigned int), 1, Out);
	/*Save Map*/
	fwrite(Map, sizeof(unsigned int), MapSize * MapSize, Out);
	/*Save Candle Lit Status*/
	fwrite(&CandleLit, sizeof(unsigned char), 1, Out);
}

void LoadMap(FILE* In)
{
	/*Load Current Position*/
	fread(&CurrentPosition, sizeof(unsigned int), 1, In);
	/*Load Map*/
	fread(Map, sizeof(unsigned int), MapSize * MapSize, In);
	/*Load Candle Lit Status*/
	fread(&CandleLit, sizeof(unsigned char), 1, In);
}
