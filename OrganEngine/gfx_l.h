#ifndef GFX_L_H
#define GFX_L_H

#include <stdint.h>

//typedef for the color struct defined in gfx_(os).c
typedef struct rgbColor_s O_color;

//Define a struct to hold the rgb values
struct rgbColor_s
{
	uint8 r;
	uint8 g;
	uint8 b;
};

//enum of the current O_color types avaliable
enum shades
{
	RED,
	BLUE,
	GREEN,
	DARK_BLUE,
	DARK_GREY,

	TOTAL_COLORS
};

//Array of O_color structs that contain all preset colors created by InitColors
extern O_color o_colors[TOTAL_COLORS];

//Draw the bottom of the screen with a certain color of pixels
/**
buffer - the memory to write the rgb data to
type - enum color type
**/
void GFX_DrawFloor(int32* buffer, int32 type);

//Draw the top of the screen with a certain color of pixels
/**
buffer - the memory to write the rgb data to
type - enum color type
**/
void GFX_DrawCeil(int32* buffer, int32 type);

//
void GFX_DrawHUD(int32* buffer);
void GFX_drawColumn(int32* dblBuffer, int32 x, int32 startY, int32 endY, O_color* color);

//Init the array of O_colors
void GFX_InitColors(void);

void GFX_DrawWalls(int32 * buffer);
#endif