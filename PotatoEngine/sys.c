//=================================================================================
//sys.c handles system related task, mostly time keeping and updating the window with events
//
//
//
//Author: Kenny Stepney
//=================================================================================


#include "p_def.h"
#include "p_win.h"

#include "sys.h"


//Time keeping variables, used to detect the amount of time passed
static double GTimePassed = 0;
static double GTimeCounter = 0;
static double GFPS = 0;


//Initializes the variables to start keeping track of the time intrevals
void Sys_InitTime(void)
{
	//Get the frequency of the processsor currently running
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//Get the FPS
	GFPS = 1.0 / (double)frequency.QuadPart;

	//Get the time
	LARGE_INTEGER timeCounter;
	QueryPerformanceCounter(&timeCounter);

	GTimeCounter = timeCounter.QuadPart;
}

//Returns the current time that has passed in seconds
float Sys_Time(void)
{
	LARGE_INTEGER timePassed;
	QueryPerformanceCounter(&timePassed);

	int64 interval = timePassed.QuadPart - GTimeCounter;
	GTimeCounter = timePassed.QuadPart;

	double secondsPassed = (double)interval * GFPS;

	GTimePassed += secondsPassed;
	return secondsPassed;
}

//Shutdown this system
void Sys_Shutdown(void)
{
	bRunning = FALSE;
}

//Send the events the OS send to over process over to be handle by the WndProc function
void Sys_SendKeyEvents(void)
{
	//Make sure is MSG type
	MSG msg;
	//PeekMessage, addr to msg, null, null, null, remove message
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}