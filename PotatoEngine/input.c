//=================================================================================
//input.c - handles key input from the system
//
//
//Author: Kenny Stepney
//=================================================================================


#include "p_def.h"
#include "input.h"

//Set the the input keys initially to zero
extern uint8 keys[NUM_KEYS] = { 0, 0, 0, 0 };


//Handle the keys that are inputted by the system(a.k.a the player)
//KEys are update in the WndProc loacted in win.c
void Inp_HandleKeys(void)
{
	if (keys[UP])
	{
		Host_Move(GPlayer->dir.x * moveSpeed, GPlayer->dir.y * moveSpeed);

	}
	if (keys[DOWN])
	{
		Host_Move(GPlayer->dir.x * -moveSpeed, GPlayer->dir.y * -moveSpeed);

	}
	if (keys[LEFT])
	{
		Host_Rot(rotSpeed);
	}
	if (keys[RIGHT])
	{
		Host_Rot(-rotSpeed);
	}
}