//=================================================================================
//main.c - main entry point of the process
//
//Notes: Initializes most of the systems used in the engine
//
//Author: Kenny Stepney
//=================================================================================

#include "p_def.h"
#include "p_win.h"

//Set the extern bool variable bRunning to false
//Records whether the process should continue running
extern uint8 bRunning = FALSE;

//The main player object
player_t player = { 0 };

//Pointer to the start  of the linkedlist, currently unused
object_t* startObject = NULL;

//Initialize main components, first system to initialize in the engine
static void Main_Init(void)
{
	//Initialize member attributes
	player.pos.x = 4.5;
	player.pos.y = 4.5;
	player.dir.x = 1;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = -0.66;
	player.height = 32;
	player.angle = 45;

	//Set the global player pointer to point to the player object
	GPlayer = &player;

	//Initialize the window
	Win_Init();
}

/**
	hInstance - instance of the program
	prevInstance - never used on modern sysytems
	lCmdLine - long string of commnadline inputs
	nShowLine - also nevered used
**/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lCmdLine, int nShowCmd)
{
	//Check if not running, set to true if it isn't running
	if (!bRunning) {
		bRunning = TRUE;
	}

	//Set the Global hinstance variable to the process instance
	GInstance = hInstance;

	//Init Systems
	//Main Timestep Loop
	Main_Init();

	//Extended styles
	Host_Init();
	Sys_InitTime();

	//Mainengine loop
	while (bRunning) 
	{
		//Get current time
		float timestep = Sys_Time();

		//Update the host by the amount in the timestep
		Host_Frame(timestep);
	}

	//Exit when running == FALSE
	return EXIT_SUCCESS;
}
