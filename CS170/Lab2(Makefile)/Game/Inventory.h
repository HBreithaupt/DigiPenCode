#ifndef INVENTORYH
#define INVENTORYH

/*Item Type*/
enum ItemType
{
	ItemType_Key,
	ItemType_Candle,
	ItemType_Lighter
};

/*Define Item Structure*/
struct Item
{
	/*Item Type*/
	enum ItemType CurrentType;
	/*Next Item*/
	struct Item* Next;
};

/*Inventory*/
extern struct Item* Inventory;

/*Function Prototypes*/
void AddItem(enum ItemType itemType);
struct Item* QueryItem(enum ItemType itemType);
void RemoveItem(enum ItemType itemType);
void DisplayInventory(void);
void DestroyInventory(void);
void SaveInventory(FILE* Out);
void LoadInventory(FILE* In);

#endif /* INVENTORYH */
