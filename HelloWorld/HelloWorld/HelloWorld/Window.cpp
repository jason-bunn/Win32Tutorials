
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker, "/subsystem:windows")

#include "stdafx.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>



// windows procedure event handler
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	// device context
	HDC hDC;

	//text for display
	char string[] = "Hello, World!";

	//switch message, condition that is met will execute
	switch (message)
	{
	case WM_CREATE:
		return 0;
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		// set txt color to blue
		SetTextColor(hDC, COLORREF(0x00FF0000));
		// display text in the middle of window
		TextOut(hDC, 150, 150, string, sizeof(string) - 1);
		EndPaint(hwnd, &paintStruct);
		return 0; 
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, message, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX windowClass;
	HWND hwnd; // window handle
	MSG msg;	// message, duh
	bool done;	//exit flag

	//fill out window class structure
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	//register window class
	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}
	//class registered, no create window

	hwnd = CreateWindowEx(NULL,		//Extended style
		"MyClass",		//class name
		"A Real Win App",		//App name
		WS_OVERLAPPEDWINDOW |		//window style
		WS_VISIBLE |
		WS_SYSMENU,
		100, 100,				//x,y coords
		400, 400,				//width, height
		NULL,					// handle to parent
		NULL,					// handle to menu
		hInstance,				//appliation instance
		NULL);					// no extra parameters

	// check if window creation failed
	if (!hwnd)
		return 0;
	
	done = false; // initialize loop condition variable
	// main message loop (finally)
	while (!done)
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT) // check for quit message
		{
			done = true;
		}
		else
		{
			// translate and dispatch to event queue
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
