#include "FrameRateController.h"
#include <Windows.h>

#pragma comment(lib, "winmm.lib")
#pragma warning(disable: 4996)

int FrameStart;
int FrameEnd;
int FrameCounter;
int MaxFrameRate;
int FrameRate;
double FrameTime;
double MinFrameRate;

FILE *frameinput;

extern FILE *output;

void FrameInitialization(void)
{
	frameinput = fopen("FrameRate.txt", "r");

	FrameCounter = 0;
	fscanf(frameinput, "%i", &MaxFrameRate);
	
	FrameRate = MaxFrameRate;
	FrameTime = 1000.0 / FrameRate;
	MinFrameRate = 1000.0 / MaxFrameRate;
	FrameEnd = 0;
}

void FrameControllerStart(void)
{
	FrameStart = timeGetTime();
	
}

void FrameControllerEnd(void)
{
	FrameEnd = timeGetTime();
	while (FrameEnd - FrameStart < MinFrameRate)
		FrameEnd = timeGetTime();

	FrameTime = FrameEnd - FrameStart;

	FrameCounter++;

	fprintf(output, "Frametime: %.2fms\n", FrameTime);
}