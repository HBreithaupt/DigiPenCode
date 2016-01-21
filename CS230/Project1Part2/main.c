#include <windows.h>
#include "FrameRateController.h"
#include "GameStateList.h"
#include "Input.h"
#include"Level1.h"
#include "Level2.h"
#include "System.h"
#include "GameStateManager.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

//Entry point of the application
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	wc.style = CS_HREDRAW | CS_VREDRAW;							/*Class style*/
	wc.lpfnWndProc = WinProc;									/*A function pointer which should point to the procedure function. Remember that the procedure function handles the window messages*/
	wc.cbClsExtra = 0;											/*The number of extra bytes you want to allocate for this window class structure. The default value is 0*/
	wc.cbWndExtra = 0;											/*The number of extra bytes you want to allocate for the window instance*/
	wc.hInstance = instance;									/*Instance of the module associated with the window. This is the 1st paramter passed to the WinMain function*/
	wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);					/*Handle to the icon class which will be displayed on the top left part of the window*/
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);					/*Handle to the cursor class which will be used in this window class*/
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		/*Handle to the class background brush. It can be a color value*/
	wc.lpszMenuName = NULL;										/*Pointer to a null terminated string which specifies the name of the menu resources used by this window class (if any)*/
	wc.lpszClassName = "Window Class Name";						/*String that specifies thw window class name. This is needed to create any window based on this window class*/

	RegisterClass(&wc);


	hWnd = CreateWindow(wc.lpszClassName,			/*The class name we chose for the window class*/
		"Win32 Sample",								/*The window caption*/
		WS_OVERLAPPEDWINDOW,						/*The style of the window, which determines if the window will have a minimize/maximize buttons, if its frame is thick or not.. */
		200,										/*The X position of the top left corner of the window. Remember that (0,0) is the top left of the monitor*/
		100,										/*The Y position of the top left corner of the window. Remember that (0,0) is the top left of the monitor*/
		640,										/*The width of the window*/
		480,										/*The heiht of the window*/
		NULL,										/*Handle to the parent window (in case this was a child window)*/
		NULL,										/*Handle to a menu (In case there is a menu for this window)*/
		instance,									/*Instance of the module associated with the window. This is the 1st paramter passed to the WinMain function*/
		NULL);										/*Pointer to a value sent to the window in the WM_CREATE message*/
	ShowWindow(hWnd, show);
	UpdateWindow(hWnd);

	UnregisterClass(wc.lpszClassName, instance);

	System_Initialize();

	GSM_Initialize(1);

	while (Current != Quit)
	{

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		FrameInitialization();

		if (Current == Restart)
		{
			Current = Previous;
			Next = Previous;
		}
		else
		{
			GSM_Update();
			pLoad();
		}

		pInitialize();

		while (Current == Next)
		{
			FrameControllerStart();
			Input_Handle();
			pUpdate();
			pDraw();
			FrameControllerEnd();
		}

		pFree();

		if (Next != Restart)
		{
			pUnload();
		}

		Previous = Current;
		Current = Next;
	}

	System_Exit();


	return (int)msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	HDC dc;           /* device context */
	PAINTSTRUCT ps;   /* the paint struct */
	/*RECT rect;*/

	switch (msg)
	{
		/* when the window is created */
		case WM_CREATE:
			break;

		/* when the rectangle is drawn */
		case WM_LBUTTONDOWN:
			break;
		
		case WM_MOUSEMOVE:
			break;

		case WM_PAINT:
			dc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		/* When it's time for the window to be closed and removed */
		

		case WM_KEYDOWN:
			if (wParam == 'Q')
				Next = Quit;
			else if (wParam == '2')
				Next = Level_2;
			break;

		

		/* called any time the window is moved */
		case WM_MOVE:
			/* Invalidate the rect to force a redraw */
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}