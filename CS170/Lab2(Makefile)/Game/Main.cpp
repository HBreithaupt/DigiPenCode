#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Command.h"
#include "Parser.h"
#include "Inventory.h"
#include "Map.h"

int main(void)
{
	/*Update Initial State*/
	int CurrentPositionX, CurrentPositionY;
	GetCurrentPosition(&CurrentPositionX, &CurrentPositionY);
	UpdateStats(CurrentPositionX, CurrentPositionY);

	/*Game Loop*/
	for (;;) /* loop forever, no compiler warning */
	{
		/*Get Input*/
		char Input[256], *Output[3] = {NULL};
		unsigned int InputLength, CurrentCharacter, WordCount;
		scanf(" %[^\n]", Input);
		/*Convert Input To Lowercase*/
		InputLength = (unsigned int)strlen(Input);
		for(CurrentCharacter = 0; CurrentCharacter < InputLength; ++CurrentCharacter)
			Input[CurrentCharacter] = (char)tolower(Input[CurrentCharacter]);
		/*Parse Input*/
		WordCount = Parse(Input, Output, 3);
		if(WordCount > 2)
		{
			/*Invalid Command*/
			printf("Too Many Command Tokens\n");
		}
		else
		{
			/*Get Command*/
			switch(GetCommand(Output[0]))
			{
				case Command_Look:
									{
										/*Get Look Parameter*/
										char Valid = 1;
										int LookPositionX = CurrentPositionX, LookPositionY = CurrentPositionY;
										switch(GetLookParam(Output[1]))
										{
											case LookParam_Up:
																--LookPositionY;
																break;
											case LookParam_Left:
																--LookPositionX;
																break;
											case LookParam_Down:
																++LookPositionY;
																break;
											case LookParam_Right:
																++LookPositionX;
																break;
											default:
																printf("Look Parameter Invalid\n");
																Valid = 0;
																break;
										}
										/*If Look Is Valid*/
										if(Valid)
										{
											/*Look*/
											Look(LookPositionX, LookPositionY);
										}
									}
									break;
				case Command_Move:
									{
										/*Get Move Parameter*/
										char Valid = 1;
										int OldPositionX = CurrentPositionX, OldPositionY = CurrentPositionY;
										switch(GetMoveParam(Output[1]))
										{
											case MoveParam_Up:
																--CurrentPositionY;
																break;
											case MoveParam_Left:
																--CurrentPositionX;
																break;
											case MoveParam_Down:
																++CurrentPositionY;
																break;
											case MoveParam_Right:
																++CurrentPositionX;
																break;
											default:
																printf("Move Parameter Invalid\n");
																Valid = 0;
																break;
										}
										/*If Move Is Valid*/
										if(Valid)
										{
											/*Update Stats*/
											char Result = UpdateStats(CurrentPositionX, CurrentPositionY);
											if(Result < 0)
											{
												/*Reset Position*/
												CurrentPositionX = OldPositionX;
												CurrentPositionY = OldPositionY;
											}
											else if(Result > 0)
											{
												/*Exit*/
												DestroyInventory();
												return 0;
											}
										}
									}
									break;
				case Command_Take:
									{
										/*Get Take Parameter*/
										char Valid = 1;
										enum ItemType TakeType;
										switch(GetTakeParam(Output[1]))
										{
											case TakeParam_Key:
																TakeType = ItemType_Key;
																break;
											case TakeParam_Candle:
																TakeType = ItemType_Candle;
																break;
											case TakeParam_Lighter:
																TakeType = ItemType_Lighter;
																break;
											default:
																printf("Take Parameter Invalid\n");
																TakeType = ItemType_Key; /* suppress potentially uninitialized warning */
																Valid = 0;
																break;
										}
										/*If Take Is Valid*/
										if(Valid)
										{
											/*Take Item*/
											TakeItem(TakeType);
										}
									}
									break;
				case Command_Use:
									{
										/*Get Use Parameter*/
										char Valid = 1;
										enum ItemType UseType;
										switch(GetTakeParam(Output[1]))
										{
											case UseParam_Key:
																UseType = ItemType_Key;
																break;
											case UseParam_Candle:
																UseType = ItemType_Candle;
																break;
											case UseParam_Lighter:
																UseType = ItemType_Lighter;
																break;
											default:
																printf("Use Parameter Invalid\n");
																UseType = ItemType_Key; /* suppress potentially uninitialized warning */
																Valid = 0;
																break;
										}
										/*If Use Is Valid*/
										if(Valid)
										{
											/*Use Item*/
											UseItem(UseType);
										}
									}
									break;
				case Command_Open:
									{
										/*Get Open Parameter*/
										switch(GetOpenParam(Output[1]))
										{
											case OpenParam_Door:
																OpenDoor();
																break;
											default:
																printf("Open Parameter Invalid\n");
																break;
										}
									}
									break;
				case Command_Inventory:
									{
										/*Display Inventory*/
										DisplayInventory();
									}
									break;
				case Command_Save:
									{
										/*Open File Name*/
										FILE* Out = fopen(Output[1], "wb");
										if(Out)
										{
											/*Save Current Position*/
											fwrite(&CurrentPositionX, sizeof(int), 1, Out);
											fwrite(&CurrentPositionY, sizeof(int), 1, Out);
											/*Save Map*/
											SaveMap(Out);
											/*Save Inventory*/
											SaveInventory(Out);
											/*Close File*/
											fclose(Out);
											/*Display Message*/
											printf("<<<File Saved>>>\n");
										}
										else
										{
											/*Invalid File Path*/
											printf("Invalid File Path\n");
										}
									}
									break;
				case Command_Load:
									{
										/*Open File Name*/
										FILE* In = fopen(Output[1], "rb");
										if(In)
										{
											/*Load Current Position*/
											fread(&CurrentPositionX, sizeof(int), 1, In);
											fread(&CurrentPositionY, sizeof(int), 1, In);
											/*Load Map*/
											LoadMap(In);
											/*Load Inventory*/
											LoadInventory(In);
											/*Close File*/
											fclose(In);
											/*Display Message*/
											printf("<<<File Loaded>>>\n");
										}
										else
										{
											/*Invalid File Path*/
											printf("Invalid File Path\n");
										}
									}
									break;
				case Command_Help:
									{
										/*Display Commands*/
										printf("Commands:\n\tLook(Up, Left, Down, Right)\n\tMove(Up, Left, Down, Right)\n\tTake(Key,Candle,Lighter)\n\tUse(Key,Candle,Lighter)\n\tOpen(Door)\n\tInventory\n\tSave(Filename)\n\tLoad(Filename)\n\tHelp\n\tExit\n");
									}
									break;
				case Command_Exit:
									/*Exit*/
									DestroyInventory();
									return 0;
				default:
									/*Invalid Command*/
									printf("Invalid Command\n");
									break;
			}
		}
	}
}
