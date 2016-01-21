#include <string.h>
#include "Command.h"

/*Command List*/
static const char* CommandList[] = 
{
	"look",
	"move",
	"take",
	"use",
	"open",
	"inventory",
	"save",
	"load",
	"help",
	"exit",
};

/*Move Parameter List*/
static const char* MoveParamList[] = 
{
	"up",
	"left",
	"down",
	"right"
};

/*Look Parameter List*/
static const char* LookParamList[] = 
{
	"up",
	"left",
	"down",
	"right"
};

/*Take Parameter List*/
static const char* TakeParamList[] = 
{
	"key",
	"candle",
	"lighter"
};

/*Use Parameter List*/
static const char* UseParamList[] = 
{
	"key",
	"candle",
	"lighter"
};

/*Open Parameter List*/
static const char* OpenParamList[] = 
{
	"door"
};

/*Function to Get Command*/
enum Command GetCommand(const char* CurrentCommand)
{
	/*Get Commands Number*/
	unsigned int CommandsNumbber = sizeof(CommandList) / sizeof(const char*);
	/*Determine Command ID*/
	unsigned int CurrentCommandID = 0;
	for(;CurrentCommandID < CommandsNumbber; ++CurrentCommandID)
	{
		/*Match Commands*/
		if(!strcmp(CurrentCommand, CommandList[CurrentCommandID]))
			return (enum Command)CurrentCommandID;
	}
	/*Invalid Command*/
	return Command_Invalid;
}

/*Function to Get Param*/
int GetParam(const char* CurrentParam, const char* ParamList[], unsigned int ParamsNumber)
{
	/*Validate Param*/
	unsigned int CurrentParamID = 0;
	if(!CurrentParam)
		return -1;
	/*Determine Param ID*/
	for(;CurrentParamID < ParamsNumber; ++CurrentParamID)
	{
		/*Match Params*/
		if(!strcmp(CurrentParam, ParamList[CurrentParamID]))
			return CurrentParamID;
	}
	/*Invalid Param*/
	return -1;
}

/*Function to Get Look Param*/
enum LookParam GetLookParam(const char* CurrentParam)
{
	/*Get Move Params Number*/
	unsigned int LookParamsNumbber = sizeof(LookParamList) / sizeof(const char*);
	int CurrentParamID = GetParam(CurrentParam, LookParamList, LookParamsNumbber);
	if(CurrentParamID >= 0)
		return (enum LookParam)CurrentParamID;
	/*Invalid Param*/
	return (enum LookParam)LookParam_Invalid;
}

/*Function to Get Move Param*/
enum MoveParam GetMoveParam(const char* CurrentParam)
{
	/*Get Move Params Number*/
	unsigned int MoveParamsNumbber = sizeof(MoveParamList) / sizeof(const char*);
	int CurrentParamID = GetParam(CurrentParam, MoveParamList, MoveParamsNumbber);
	if(CurrentParamID >= 0)
		return (enum MoveParam)CurrentParamID;
	/*Invalid Param*/
	return MoveParam_Invalid;
}

/*Function to Get Take Param*/
enum TakeParam GetTakeParam(const char* CurrentParam)
{
	/*Get Take Params Number*/
	unsigned int TakeParamsNumbber = sizeof(TakeParamList) / sizeof(const char*);
	int CurrentParamID = GetParam(CurrentParam, TakeParamList, TakeParamsNumbber);
	if(CurrentParamID >= 0)
		return (enum TakeParam)CurrentParamID;
	/*Invalid Param*/
	return TakeParam_Invalid;
}

/*Function to Get Use Param*/
enum UseParam GetUseParam(const char* CurrentParam)
{
	/*Get Use Params Number*/
	unsigned int UseParamsNumbber = sizeof(UseParamList) / sizeof(const char*);
	int CurrentParamID = GetParam(CurrentParam, UseParamList, UseParamsNumbber);
	if(CurrentParamID >= 0)
		return (enum UseParam)CurrentParamID;
	/*Invalid Param*/
	return UseParam_Invalid;
}

/*Function to Get Open Param*/
enum OpenParam GetOpenParam(const char* CurrentParam)
{
	/*Get Open Params Number*/
	unsigned int OpenParamsNumbber = sizeof(OpenParamList) / sizeof(const char*);
	int CurrentParamID = GetParam(CurrentParam, OpenParamList, OpenParamsNumbber);
	if(CurrentParamID >= 0)
		return (enum OpenParam)CurrentParamID;
	/*Invalid Param*/
	return OpenParam_Invalid;
}
