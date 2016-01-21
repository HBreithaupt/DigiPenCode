#ifndef COMMANDH
#define COMMANDH

/*Command Enumeration*/
enum Command
{
	Command_Look,
	Command_Move,
	Command_Take,
	Command_Use,
	Command_Open,
	Command_Inventory,
	Command_Save,
	Command_Load,
	Command_Help,
	Command_Exit,
	Command_Invalid
};

/*Move Param Enumeration*/
enum MoveParam
{
	MoveParam_Up,
	MoveParam_Left,
	MoveParam_Down,
	MoveParam_Right,
	MoveParam_Invalid
};

/*Look Param Enumeration*/
enum LookParam
{
	LookParam_Up,
	LookParam_Left,
	LookParam_Down,
	LookParam_Right,
	LookParam_Invalid
};

/*Take Param Enumeration*/
enum TakeParam
{
	TakeParam_Key,
	TakeParam_Candle,
	TakeParam_Lighter,
	TakeParam_Invalid
};

/*Use Param Enumeration*/
enum UseParam
{
	UseParam_Key,
	UseParam_Candle,
	UseParam_Lighter,
	UseParam_Invalid
};

/*Open Param Enumeration*/
enum OpenParam
{
	OpenParam_Door,
	OpenParam_Invalid
};

/*Function Prototypes*/
enum LookParam GetLookParam(const char* CurrentParam);
enum Command GetCommand(const char* CurrentCommand);
enum MoveParam GetMoveParam(const char* CurrentParam);
enum TakeParam GetTakeParam(const char* CurrentParam);
enum OpenParam GetOpenParam(const char* CurrentParam);
enum UseParam GetUseParam(const char* CurrentParam);

#endif /* COMMANDH */
