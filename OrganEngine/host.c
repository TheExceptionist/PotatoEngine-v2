//=================================================================================
//host.c - abstraction away from the Systems Programming, manages updating the systems active 
//
//
//Author: Kenny Stepney
//=================================================================================

#include "p_def.h"

//Variables that determine if a timestep passed through ValiadiateTimestep is valid
static double timeAcc = 0;
static double oldTimeAcc = 0;

//The worldMap that is used to draw out the 3D walls and cubes
extern uint8 worldMap[mapWidth][mapHeight] =
{
	{ 2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 2,0,0,2,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,0,0,4,1 },
	{ 2,0,0,2,0,0,3,0,0,0,3,0,0,0,3,0,0,0,3,0,5,0,4,1 },
	{ 2,0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,2,3,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,2,0,0,0,0,2,0,2,0,2,0,2,5,2,0,0,0,1 },
	{ 1,0,0,0,0,0,2,0,0,0,0,2,0,2,0,2,0,2,0,2,0,0,0,1 },
	{ 1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,2,0,2,2,2,0,2,0,2,0,2,0,2,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,2,0,0,0,1 },
	{ 1,2,2,2,2,2,2,2,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,2,0,0,3,0,0,0,0,4,4,0,0,4,4,0,0,1 },
	{ 1,0,0,0,0,0,0,2,3,3,3,3,3,0,0,4,4,0,0,4,4,0,0,1 },
	{ 1,0,0,0,0,0,0,2,0,0,3,0,0,0,0,0,0,0,0,0,0,0,5,1 },
	{ 1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,4,4,0,0,4,4,0,0,1 },
	{ 1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,4,4,0,0,4,4,0,0,1 },
	{ 1,4,4,4,4,4,4,4,4,0,0,2,2,2,2,2,2,2,2,2,2,2,2,1 },
	{ 1,4,0,4,0,0,0,0,4,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,0,0,0,5,0,4,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,4,0,0,0,0,4,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,4,4,4,4,4,4,4,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

//Detects where the rays cast by the player have visited, currently unused
extern uint8 visitedMap[mapWidth][mapHeight] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};


//Init some systems
void Host_Init(void)
{
	//Init GFX System
	GFX_Init();
}

//Check if the timestep passed is large enough.
int Host_ValidateTimestep(int timestep)
{
	//Accumulate the timesteps until the
	//different between the new and old are > 1
	timeAcc += timestep;

	if (timeAcc - oldTimeAcc < 1) {
		return 0;
	}

	oldTimeAcc = timeAcc;
	return 1;
}

//Update systems being used
/**
	timestep - the amount of time to update by, must be significant enough
**/
void Host_Frame(float timestep)
{
	if (Host_ValidateTimestep(timestep))
	{
		return;
	}

	//Check from any OS events, most focused toward key input
	Sys_SendKeyEvents();

	//Update the graphics
	GFX_Update();
}

//Shutdown all systems currently being used
void Host_Shutdown(void)
{
	//Shutdown both the graphics and system
	GFX_Shutdown();
	Sys_Shutdown();
}


//Move the player object in a certain direction
//Fails if the player is about ot move onto a wall or solid map object

/**
	float x - position to move the player in the x direction
	float y - position to move the player in the y direction
**/
void Host_Move(float x, float y)
{
	if (worldMap[(int)((GPlayer->pos.x + x))][(int)(GPlayer->pos.y)] == 5)
	{
		GPlayer->score++;
		worldMap[(int)((GPlayer->pos.x + x))][(int)(GPlayer->pos.y)] = 0;
	}

	if (worldMap[(int)(GPlayer->pos.x)][(int)(GPlayer->pos.y + y)] == 5)
	{
		GPlayer->score++;
		worldMap[(int)(GPlayer->pos.x)][(int)(GPlayer->pos.y + y)] = 0;
	}

	if (worldMap[(int)((GPlayer->pos.x + x))][(int)(GPlayer->pos.y)] == NULL) GPlayer->pos.x += x;
	if (worldMap[(int)(GPlayer->pos.x)][(int)(GPlayer->pos.y + y)] == NULL) GPlayer->pos.y += y;
}

//Rotate the player object with a certain speed

/**
	float speed - the speed to rotate the player by
**/
void Host_Rot(float speed)
{
	float oldDirX = GPlayer->dir.x;
	float oldPlaneX = GPlayer->plane.x;

	GPlayer->dir.x = GPlayer->dir.x * cos(speed) - GPlayer->dir.y * sin(speed);
	GPlayer->dir.y = oldDirX * sin(speed) + GPlayer->dir.y * cos(speed);
	
	GPlayer->plane.x = GPlayer->plane.x * cos(speed) - GPlayer->plane.y * sin(speed);
	GPlayer->plane.y = oldPlaneX * sin(speed) + GPlayer->plane.y * cos(speed);
}
