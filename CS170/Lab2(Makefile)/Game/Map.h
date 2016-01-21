#ifndef MAPH
#define MAPH

#include "Inventory.h" /* ItemType */

/*Map Cells (Every Cell State Denoted By One Bit)*/
enum MapCell
{
	MapCell_Empty   = 0,
	MapCell_Void    = 1,
	MapCell_Key	    = MapCell_Void << 1,
	MapCell_Candle  = MapCell_Key << 1,
	MapCell_Lighter = MapCell_Candle << 1,
	MapCell_Locked  = MapCell_Lighter << 1,
	MapCell_Dark	= MapCell_Locked << 1,
	MapCell_Gold	= MapCell_Dark << 1
};

/*Function Prototypes*/
void GetCurrentPosition(int* CurrentPositionX, int* CurrentPositionY);
unsigned int GetCurrentCell(void);
void Look(int NewPositionX, int NewPositionY);
char UpdateStats(int NewPositionX, int NewPositionY);
char TakeItem(enum ItemType CurrentItem);
char UseItem(enum ItemType CurrentItem);
char OpenDoor(void);
void SaveMap(FILE* Out);
void LoadMap(FILE* In);

#endif /* MAPH */
