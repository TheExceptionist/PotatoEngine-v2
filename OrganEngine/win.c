//=================================================================================
//Win.c - holds all windows (OS) related code
//
//
//Author: Kenny Stepney
//=================================================================================

#include "p_def.h"
#include "p_win.h"

//Default windows produre called to update the window with os events
/**
hwnd - handle to the window
uMsg - os message to the window
wParam - extra data
lParam - more extra data
**/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	//Get Keys
	//Use default prodecure

	switch (uMsg)
	{
		case WM_ACTIVATE:
			
			break;
		case WM_CREATE:
		
			break;
		case WM_CLOSE:
			if (MessageBox(hwnd, "Really quit?", "Organ Engine", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			break;
		case WM_DESTROY:
			Host_Shutdown();
			break;
		case WM_KEYDOWN:
			if (wParam == VK_UP)
				keys[UP] = 1;
			if(wParam == VK_DOWN)
				keys[DOWN] = 1;
			if(wParam == VK_LEFT)
				keys[LEFT] = 1;
			if(wParam == VK_RIGHT)
				keys[RIGHT] = 1;

			Inp_HandleKeys();
			break;
		case WM_KEYUP:
			if (wParam == VK_UP)
				keys[UP] = 0;
			if (wParam == VK_DOWN)
				keys[DOWN] = 0;
			if (wParam == VK_LEFT)
				keys[LEFT] = 0;
			if (wParam == VK_RIGHT)
				keys[RIGHT] = 0;

			Inp_HandleKeys();
			break;
		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
	}

	return result;
}

//Register the window class to by displayed by a window
static int32 Win_Register(void)
{
	WNDCLASS wc = {
		NULL,
		WndProc,
		NULL,
		NULL,
		GInstance,
		LoadIcon(GInstance, NULL),
		LoadCursor(GInstance, NULL),
		NULL,
		TITLE_NAME,
		CLASS_NAME
	};

	if (!RegisterClass(&wc))
	{
		int i = 0;
		sprintf(stdout, "Could not register window class!");
		scanf(stdin, "", &i);
		exit(EXIT_FAILURE);
	}

}


//Create the window instance and display it
static void Win_CreateWindow(void)
{
	DWORD dwExStyle = 0;
	DWORD dwWindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.left = r.top = 0;
	r.right = WINDOW_WIDTH;
	r.bottom = WINDOW_HEIGHT;
	AdjustWindowRectEx(&r, dwWindowStyle, 0, dwExStyle);

	Con_WriteConsole("Creating a new window...");

	hwndMainWindow = CreateWindowEx(
		dwExStyle,
		CLASS_NAME,
		TITLE_NAME,
		dwWindowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		GInstance,
		NULL
	);

	Con_WriteConsole("Showing the new window...");
	ShowWindow(hwndMainWindow, SW_SHOWDEFAULT);

	Con_WriteConsole("Filling the window with the color black..");
	HDC hdcDeviceContext = GetDC(hwndMainWindow);
	PatBlt(hdcDeviceContext, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACKNESS);
	ReleaseDC(hwndMainWindow, hdcDeviceContext);
}

//Initialize the window systems
void Win_Init(void)
{
	Con_WriteConsole("Initializing Windows Subsystems...");
	Win_Register();
	Win_CreateWindow();
	Con_WriteConsole("Windows Subsystems Initialized!");
}

