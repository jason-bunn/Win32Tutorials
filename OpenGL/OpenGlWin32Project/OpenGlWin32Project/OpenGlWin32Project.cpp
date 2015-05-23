// OpenGlWin32Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenGlWin32Project.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HGLRC glRenderContext;
int gHeight = 800;
int gWidth = 600;
bool bExit;
HDC wndDC;
HWND hWnd;
float angle;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	angle = 0.0f;
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OPENGLWIN32PROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENGLWIN32PROJECT));
	
	InitGL();
	glClear(GL_COLOR_BUFFER_BIT);
	bExit = false;
	//main game loop
	while (!bExit)
	{
		
		
		// Main message loop:
		PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT)
		{
			bExit = true;
		}
		else
		{
			//draw functions
			Render();

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		
	}

	

	return (int) msg.wParam;
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return 1;
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height <= 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	angle += 1.0f;
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -30.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	DrawRobot(0.0f,0.0f,0.0f);
	glPopMatrix();
	glFlush();
	SwapBuffers(wndDC);
}

void DrawRobot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glBegin(GL_POLYGON);

	/*      This is the top face*/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	/*      This is the front face*/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	/*      This is the right face*/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	/*      This is the left face*/
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	/*      This is the bottom face*/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	/*      This is the back face*/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	glEnd();
	glPopMatrix();
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENGLWIN32PROJECT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_CLIPSIBLINGS| WS_CLIPCHILDREN |WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      0, 0, gHeight, gWidth, NULL, NULL, hInstance, NULL);
   
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   SetForegroundWindow(hWnd);
   ReSizeGLScene(gWidth, gHeight);
   UpdateWindow(hWnd);
   
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;
	wndDC = GetDC(hWnd);
	int thisPixelFormat;
	PIXELFORMATDESCRIPTOR pfd;


	switch (message)
	{
	case WM_CREATE:
		pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		
		thisPixelFormat = ChoosePixelFormat(wndDC, &pfd);
		SetPixelFormat(wndDC, thisPixelFormat, &pfd);

		if ((glRenderContext = wglCreateContext(wndDC)) == NULL)
		{
			MessageBox(hWnd, (LPCWSTR)"Failed to create the OpenGL render context",
				(LPCWSTR)"OpenGL Rendering Conext Error", MB_OK);
			bExit = true;
			break;
		}
		if ((wglMakeCurrent(wndDC, glRenderContext)) == NULL)
		{
			MessageBox(hWnd, (LPCWSTR)"Failed to make gl window current",
				(LPCWSTR)"OpenGl makecurrent Error", MB_OK);
			bExit = true;
			break;
		}

		MessageBoxA(0, (char*)glGetString(GL_VERSION), "OpenGl Version", 0);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		
		//hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		bExit = true;
		wglMakeCurrent(wndDC, NULL);
		wglDeleteContext(glRenderContext);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
