#include <stdlib.h>
#include <stdio.h>
#include "Inventory.h"

/*Declare Inventory*/
struct Item* Inventory = NULL;

void AddItem(enum ItemType itemType)
{
	/*Create Item*/
	struct Item* NewItem = (struct Item*)malloc(sizeof(struct Item));
	NewItem->CurrentType = itemType;
	/*Add Item*/
	NewItem->Next = Inventory;
	/*Update Inventory*/
	Inventory = NewItem;
}

struct Item* QueryItem(enum ItemType itemType)
{	
	/*Query Item*/
	struct Item* CurrentItem = Inventory;
	for(; CurrentItem != NULL; CurrentItem = CurrentItem->Next)
	{
		/*If Item Is Found*/
		if(CurrentItem->CurrentType == itemType)
			return CurrentItem;
	}
	/*Item Not Found*/
	return NULL;
}


void RemoveItem(enum ItemType itemType)
{
	/*Validate Inventory*/
	struct Item* CurrentItem = Inventory;
	if(!CurrentItem)
		return;

	/*If Item To Remove Is The Inventory Head*/
	if(Inventory->CurrentType == itemType)
	{
		/*Remove Item*/
		Inventory = Inventory->Next;
		free(CurrentItem);
		return;
	}

	/*Find Item*/
	for(; (CurrentItem->Next != NULL) && (CurrentItem->Next->CurrentType != itemType); CurrentItem = CurrentItem->Next)
	{
	}

	/*If Item Is Found*/
	if(CurrentItem->Next)
	{
		/*Remove Item*/
		struct Item* RemoveItem = CurrentItem->Next;
		CurrentItem->Next = CurrentItem->Next->Next;
		free(RemoveItem);
	}
}

void DisplayInventory(void)
{
	/*If Inventory Is Empty*/
	if(!Inventory)
	{
		printf("Inventory Is Empty\n");
	}
	else
	{
		/*Display Items*/
		struct Item* CurrentItem = Inventory;
		printf("Inventory:\n");
		while(CurrentItem != NULL)
		{
			/*Display Item*/
			switch(CurrentItem->CurrentType)
			{
				case ItemType_Key:
								printf("\tKey\n");
								break;
				case ItemType_Candle:
								printf("\tCandle\n");
								break;
				case ItemType_Lighter:
								printf("\tLighter\n");
								break;
			}
			/*Move To Next Item*/
			CurrentItem = CurrentItem->Next;
		}
	}
}

void DestroyInventory(void)
{
	/*Destroy Item*/
	struct Item* CurrentItem = Inventory;
	while(CurrentItem != NULL)
	{
		/*Get Next Item*/
		struct Item* NextItem = CurrentItem->Next;
		/*Free Item*/
		free(CurrentItem);
		/*Move To Next Item*/
		CurrentItem = NextItem;
	}
	/*Reset Inventory*/
	Inventory = NULL;
}

void SaveInventory(FILE* Out)
{
	/*Count Items*/
	unsigned int ItemsCount = 0;
	struct Item* CurrentItem = Inventory;
	for(; CurrentItem != NULL; CurrentItem = CurrentItem->Next, ++ItemsCount)
	{
	}
	
	/*Save Item Count*/
	fwrite(&ItemsCount, sizeof(unsigned int), 1, Out);

	/*Save Items*/
	CurrentItem = Inventory;
	for(; CurrentItem != NULL; CurrentItem = CurrentItem->Next)
	{
		/*Save Item*/
		fwrite(&CurrentItem->CurrentType, sizeof(enum ItemType), 1, Out);
	}
}

void LoadInventory(FILE* In)
{
	/*Destroy Old Inventory*/
	unsigned int ItemsCount = 0;
	DestroyInventory();
	/*Load Item Count*/
	fread(&ItemsCount, sizeof(unsigned int), 1, In);
	/*Load Items*/
	while(ItemsCount--)
	{
		/*Load Item*/
		enum ItemType CurrentType;
		fread(&CurrentType, sizeof(enum ItemType), 1, In);
		/*Add Item*/
		AddItem(CurrentType);
	}
}
